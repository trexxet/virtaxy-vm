import re

instr = open('ISA.txt')
opcodes = open('generated/opcodes.h', 'w')
for line in instr:
    words = re.split('\W+', line)
    string = '#define ' + words[1].upper()
    for i in range(2, 4):
        if words[i].startswith('reg'):
            string += '_REG'
        elif words[i].startswith('num'):
            string += '_NUM'
        else:
            string += '_NONE'
    opcodes.write(string + '\t\t 0x' + words[0] + '\n')
opcodes.close()
instr.close()

