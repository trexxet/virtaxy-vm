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
    arg3 = OPdef[4]
    if not OPtree.get(instr):
        OPtree[instr] = {}
    if not OPtree[instr].get(arg1):
        OPtree[instr][arg1] = {}
    if not OPtree[instr][arg1].get(arg2):
        OPtree[instr][arg1][arg2] = []
    OPtree[instr][arg1][arg2].append(arg3)
OPtree = OrderedDict(sorted(OPtree.items()))
opcodes.close()


# Generate code
asm = open('asm_generated.c', 'w')

for instr, args in OPtree.items():
    code = 'IF_INSTR(%s)\n{\n' % (instr.lower())
    for arg1, args2 in args.items():
        code += '\tif (arg1.type == %s)\n\t{\n' % (arg1)
        for arg2, args3 in args2.items():
            code += '\t\tif (arg2.type == %s)\n\t\t{\n' % (arg2)
            for arg3 in args3:
                code += '\t\t\tif (arg3.type == %s)\n\t\t\t{\n' % (arg3)
                code += '\t\t\t\tCHECK_PROGRAM_SIZE;\n'
                code += '\t\t\t\tOPCODE = %s_%s_%s_%s;\n' % (instr, arg1, arg2, arg3)
                for i, arg in enumerate([arg1, arg2, arg3]):
                    if arg == 'REG':
                        code += '\t\t\t\tARG%d = REG_NUM(arg%d.str);\n' % (i + 1, i + 1)
                    if arg == 'NUM':
                        code += '\t\t\t\tARG_TO_NUM(arg%d.str, &ARG%d, &S);\n' % (i + 1, i + 1)
                    if arg == 'NONE':
                        code += '\t\t\t\tARG%d = 0;\n' % (i + 1)
                code += '\t\t\t\tASSEMBLED;\n'
                code += '\t\t\t}\n'
            code += '\t\t\tINVALID_ARG3;\n';
            code += '\t\t}\n'
        code += '\t\tINVALID_ARG2;\n'
        code += '\t}\n'
    code += '\tINVALID_ARG1;\n'
    code += '}\n\n'
    asm.write(code)
asm.close()

