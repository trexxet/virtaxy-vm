import re
from collections import OrderedDict

# Create opcodes tree
opcodes = open('../common/generated/opcodes.h')
OPtree = {}

for line in opcodes:
    OPdef = re.split('[\s_+]', line)
    instr = OPdef[1]
    arg1 = OPdef[2]
    arg2 = OPdef[3]
    if not OPtree.get(instr):
        OPtree[instr] = {}
    if not OPtree[instr].get(arg1):
        OPtree[instr][arg1] = []
    OPtree[instr][arg1].append(arg2)
OPtree = OrderedDict(sorted(OPtree.items()))
opcodes.close()


# Generate code
asm = open('asm_generated.c', 'w')

for instr, args in OPtree.items():
    code = 'IF_INSTR(' + instr.lower() + ')\n{\n'
    for arg1, args2 in args.items():
        code += '\tif (arg1.type == ' + arg1 + ')\n\t{\n'
        for arg2 in args2:
            code += '\t\tif (arg2.type == ' + arg2 + ')\n\t\t{\n'
            code += '\t\t\tCHECK_PROGRAM_SIZE;\n'
            code += '\t\t\tOPCODE = ' + instr + '_' + arg1 + '_' + arg2 + ';\n'
            if arg1 == 'REG':
                code += '\t\t\tARG1 = REG_NUM(arg1.str);\n'
            if arg1 == 'NUM':
                code += '\t\t\tARG_TO_NUM(arg1.str, &ARG1, &S);\n'
            if arg1 == 'NONE':
                code += '\t\t\tARG1 = 0;\n'
            if arg2 == 'REG':
                code += '\t\t\tARG2 = REG_NUM(arg2.str);\n'
            if arg2 == 'NUM':
                code += '\t\t\tARG_TO_NUM(arg2.str, &ARG2, &S);\n'
            if arg2 == 'NONE':
                code += '\t\t\tARG2 = 0;\n'
            code += '\t\t\tASSEMBLED;\n'
            code += '\t\t}\n'
        code += '\t\tINVALID_ARG2;\n'
        code += '\t}\n'
    code += '\tINVALID_ARG1;\n'
    code += '}\n\n'
    asm.write(code)
asm.close()

