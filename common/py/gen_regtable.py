import re
from itertools import product

# Load registers description file
regs_desc = open('Registers.txt')
patternList, groups = [], []
serviceRegs = []
Public = Private = False
groupID = 0

for line in regs_desc:
    words = re.split('[, ():\n]+', line)
    if words[0] == 'Groups':
        groups = list(enumerate(words[1]))
        groupID = len(groups)
    elif words[0] == 'Public':
        Public, Private = True, False
    elif words[0] == 'Private':
        Public, Private = False, True
    elif words[0] != '':
        bitstart = int(words[1])
        bitend = int(words[2])
        bitmask = '0x%016x' % (((1 << (bitend - bitstart + 1)) - 1) << bitstart)
        if Public or Private:
            serviceRegs.append([words[0], groupID, bitmask, bitstart, int(Private)])
            groupID += 1
        else:
            patternList.append([words[0], bitmask, bitstart, 0])
regs_desc.close()

# Form registers list
matchedList = list(product(groups, patternList))
regList = list(map(lambda x: [x[1][0].replace('?', x[0][1]), x[0][0], x[1][1], x[1][2], x[1][3]],\
                   matchedList)) + serviceRegs

# Write registers table to file
regs = open('generated/registers.h', 'w')
# Register item definition
regs.write('typedef struct {' +\
           '\n\tchar name[8];' +\
           '\n\tuint8_t group;' +\
           '\n\tuint64_t bitmask;' +\
           '\n\tuint8_t shl;' +\
           '\n\tuint8_t private;' +\
           '\n} reg_t;\n\n')
regs.write('#define NUM_OF_REGNAMES ' + str(len(regList)) + '\n')
regs.write('#define NUM_OF_REGISTERS ' + str(groupID) + '\n\n')
regs.write('reg_t static regTable[NUM_OF_REGNAMES] = {\n\n')
for reg in regList:
    regItem = '%-19s' % ('{ .name = "' + str(reg[0]) + '",')
    regItem += '%-14s' % ('.group = ' + str(reg[1]) + ',')
    regItem += '%-33s' % ('.bitmask = ' + str(reg[2]) + ',')
    regItem += '%-13s' % ('.shl = ' + str(reg[3]) + ',')
    regItem += '.private = ' + str(reg[4]) + ' },\n'
    regs.write(regItem)
regs.write('\n};\n')
regs.close()

