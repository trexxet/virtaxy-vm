import re

# Load ISA description
instr = open('ISA_description.txt')
opcodes = open('generated/opcodes.h', 'w')

# Form opcodes list
for line in instr:
    words = line.split('-')[0]
    words = re.split('\W+', words)
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
    opcodes.write('%-32s' % (string) + '0x' + words[0] + '\n')
opcodes.close()
instr.close()

