import sys, re
from functools import reduce

ISAName = sys.argv[1]
genISAPath = '../isa/' + ISAName
genPath = '../generated/' + ISAName

# Load opcodes
opcodes = open(genPath + '/opcodes.h')
OPlist = {}
for line in opcodes:
    OPdef = re.split('\s+', line)
    OPname = OPdef[1]
    OPcode = OPdef[2]
    OPlist[OPcode] = OPname
opcodes.close()

# Generate code
machine = open(genPath + '/machine.c', 'w')
ISA = open(genISAPath + '/ISA.txt')
code = []

for line in ISA:
    words = []
    # Check if we have a new opcode
    try:
        words = re.split('\W+', line)
        int(words[0], 16)
    except ValueError:
        # If not, insert code to existing entry
        code.insert(-1, line)
        continue
    # Write existing opcode entry
    if (code):
        machine.write(reduce((lambda s1, s2: s1 + s2), code))
        code = []
    # Create new opcode entry
    code = ['case %s:\n' % (OPlist.get('0x%s' % words[0])), '\tbreak;\n']
machine.write(reduce((lambda s1, s2: s1 + s2), code))

ISA.close()
machine.close()

