import sys, re, os

ISAName = sys.argv[1]
genSrcPath = '../isa/' + ISAName
genDstPath = '../generated/' + ISAName

# Load ISA description
instr = open(genSrcPath + '/ISA.txt')
if not os.path.exists(genDstPath):
    os.makedirs(genDstPath)
opcodes = open(genDstPath + '/opcodes.h', 'w')

# Form opcodes list
for line in instr:
    words = line.split('-')[0]
    words = re.split('\W+', words)
    # Proceed if line is an opcode definition
    try:
        int(words[0], 16)
    except ValueError:
        continue
    string = '#define ' + words[1].upper()
    # Set 5 words
    while len(words) < 5:
        words.append('')
    while len(words) > 5:
        words.pop()
    # Form opcode name
    for i in range(2, 5):
        if words[i].startswith('reg'):
            string += '_REG'
        elif words[i].startswith('num'):
            string += '_NUM'
        else:
            string += '_NONE'
    opcodes.write('%-32s' % string + '0x' + words[0] + '\n')
opcodes.close()
instr.close()

