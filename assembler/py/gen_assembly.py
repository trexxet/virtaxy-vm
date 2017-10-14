import re

opcodes = open('generated/opcodes.h')
asm = open('generated/asm_generated.c', 'w')
prevWord = ''
for line in opcodes:
    words = re.split('[\s_+]', line)
    if prevWord != words[1]:
        if prevWord != '':
            asm.write('}\n\n')
        asm.write('IF_INSTR(' + words[1].lower() + ')\n{\n')
        prevWord = words[1]
    if words[2] == 'NUM':
        asm.write('\tif (arg1.type == NUM)\n\t{\n\t\t')
        asm.write('CHECK_PROGRAM_SIZE(2);\n\t\t')
        asm.write('NEXT_COMMAND = ' + words[1] + '_NUM;\n\t\t')
        asm.write('NEXT_COMMAND = atoi(arg1.str);\n\t\t')
        asm.write('return 0;\n\t}\n')
    elif words[2] == 'REG':
        asm.write('\tif (arg1.type == REG)\n\t{\n')
        if words[3] == 'NUM':
            asm.write('\t\tif (arg2.type == NUM)\n\t\t{\n\t\t\t')
            asm.write('CHECK_PROGRAM_SIZE(3);\n\t\t\t')
            asm.write('NEXT_COMMAND = ' + words[1] + '_REG_NUM;\n\t\t\t')
            asm.write('NEXT_COMMAND = REG_NUM(arg1.str);\n\t\t\t')
            asm.write('NEXT_COMMAND = atoi(arg2.str);\n\t\t\t')
            asm.write('return 0;\n\t\t}\n')
        elif words[3] == 'REG':
            asm.write('\t\tif (arg2.type == REG)\n\t\t{\n\t\t\t')
            asm.write('CHECK_PROGRAM_SIZE(3);\n\t\t\t')
            asm.write('NEXT_COMMAND = ' + words[1] + '_REG_REG;\n\t\t\t')
            asm.write('NEXT_COMMAND = REG_NUM(arg1.str);\n\t\t\t')
            asm.write('NEXT_COMMAND = REG_NUM(arg2.str);\n\t\t\t')
            asm.write('return 0;\n\t\t}\n')
        else:
            asm.write('\t\tif (arg2.type == NONE)\n\t\t{\n\t\t\t')
            asm.write('CHECK_PROGRAM_SIZE(3);\n\t\t\t')
            asm.write('NEXT_COMMAND = ' + words[1] + '_REG;\n\t\t\t')
            asm.write('NEXT_COMMAND = REG_NUM(arg1.str);\n\t\t\t')
            asm.write('return 0;\n\t\t}\n')
        asm.write('\t}\n')
    else:
        asm.write('\tif (arg1.type == NONE)\n\t{\n\t\t')
        asm.write('CHECK_PROGRAM_SIZE(1);\n\t\t')
        asm.write('NEXT_COMMAND = ' + words[1] + ';\n\t\t')
        asm.write('return 0;\n\t}\n')
asm.write('}')
opcodes.close()
asm.close()

