import re
from itertools import product

# Load registers description file
regs_desc = open('Registers.txt')
patternList = []
groups = []

for line in regs_desc:
    words = re.split('[, ():\n]+', line)
    if words[0] == 'Groups':
        groups = list(words[1])        
    elif words[0] != '':
        patternList.append([words[0], words[1], words[2]])
regs_desc.close()

# Form registers list
matchedList = list(product(groups, patternList))
regList = list(map(lambda x: [x[1][0].replace('?', x[0]), x[1][1], x[1][2]], matchedList))

# Write registers table to file
regs = open('generated/registers.h', 'w')
regs.write('typedef struct {\n\tchar name[8];\n\tuint8_t bits_start, bits_end;\n} reg_t;\n\n')
regs.write('#define NUM_OF_REGISTERS ' + str(len(regList)) + '\n\n')
regs.write('reg_t reg[NUM_OF_REGISTERS] = {\n\n')
for i, reg in enumerate(regList):
    regItem = '{\t.name = "' + str(reg[0]) + '", \t'
    regItem += '\t.bits_start = ' + str(reg[1]) + ', \t'
    regItem += '\t.bits_end = ' + str(reg[2]) + ' \t}'
    if i < len(regList) - 1:
        regItem += ',\n'
    regs.write(regItem)
regs.write('\n\n};\n')
regs.close()

