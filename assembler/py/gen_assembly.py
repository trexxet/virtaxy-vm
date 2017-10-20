import re
from collections import OrderedDict

# Create opcodes tree
opcodes = open('generated/opcodes.h')
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
asm = open('generated/asm_generated.c', 'w')

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
                code += '\t\t\tARG1 = strtol(arg1.str, NULL, 0);\n'
            if arg1 == 'NONE':
                code += '\t\t\tARG1 = 0;\n'
            if arg2 == 'REG':
                code += '\t\t\tARG2 = REG_NUM(arg2.str);\n'
            if arg2 == 'NUM':
                code += '\t\t\tARG2 = strtol(arg2.str, NULL, 0);\n'
            if arg2 == 'NONE':
                code += '\t\t\tARG2 = 0;\n'
            code += '\t\t\tasm_err = 0; goto assembled;\n'
            code += '\t\t}\n'
        code += '\t\tasm_err = INVALID_ARGS; invalArg = 2; goto assembled;\n'
        code += '\t}\n'
    code += '\tasm_err = INVALID_ARGS; invalArg = 1; goto assembled;\n'
    code += '}\n\n'
    asm.write(code)
asm.close()

