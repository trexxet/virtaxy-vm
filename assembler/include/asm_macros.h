// Macros for generated assembler code

#pragma once

#define CHECK_PROGRAM_SIZE(incsize)                        \
	if (P.maxSize - P.size < incsize)                  \
		P.ops = (instruction *) realloc(P.ops,     \
			  (P.maxSize += P.maxSize * 2) * sizeof(instruction))

#define IF_INSTR(instr) if (strcmp(instrStr, #instr) == 0)

#define OPCODE P.ops[P.size].opcode
#define ARG1   P.ops[P.size].arg1
#define ARG2   P.ops[P.size].arg2

