import re
from itertools import product

# Load registers description file
regs_desc = open('Registers.txt')
patternList, groups = [], []
serviceRegsPublic, serviceRegsPrivate = [], []
Public = Private = False

for line in regs_desc:
    words = re.split('[, ():\n]+', line)
    if words[0] == 'Groups':
        groups = list(words[1])
    elif words[0] == 'Public':
        Public, Private = True, False
    elif words[0] == 'Private':
        Public, Private = False, True
    elif words[0] != '':
        if Public:
            serviceRegsPublic.append([words[0], words[1], words[2], 0])
        elif Private:
            serviceRegsPrivate.append([words[0], words[1], words[2], 1])
        else:
            patternList.append([words[0], words[1], words[2], 0])
regs_desc.close()

# Form registers list
matchedList = list(product(groups, patternList))
regList = serviceRegsPublic + serviceRegsPrivate
regList += list(map(lambda x: [x[1][0].replace('?', x[0]), x[1][1], x[1][2], x[1][3]], matchedList))

# Write registers table to file
regs = open('generated/registers.h', 'w')
regs.write('typedef struct {\n\tchar name[8];\n\tuint8_t bits_start, bits_end;\n\tuint8_t private;\n} reg_t;\n\n')
regs.write('#define NUM_OF_REGISTERS ' + str(len(regList)) + '\n\n')
regs.write('reg_t reg[NUM_OF_REGISTERS] = {\n\n')
for i, reg in enumerate(regList):
    regItem = '{ .name = "' + str(reg[0]) + '", \t'
    regItem += '.bits_start = ' + str(reg[1]) + ', \t'
    regItem += '.bits_end = ' + str(reg[2]) + ',  \t'
    regItem += '.private = ' + str(reg[3]) + ' \t},\n'
    regs.write(regItem)
regs.write('\n};\n')
regs.close()

