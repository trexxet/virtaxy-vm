// Functions & macros for generated assembler code

#pragma once

#define CHECK_PROGRAM_SIZE                             \
	if (P.maxSize - P.size < 1)                    \
		P.ops = (instruction *) realloc(P.ops, \
			  (P.maxSize += P.maxSize / 2) * sizeof(instruction))

#define IF_INSTR(instr) if (strcmp(instrStr, #instr) == 0)

#define OPCODE P.ops[P.size].opcode
#define ARG1   P.ops[P.size].arg1
#define ARG2   P.ops[P.size].arg2
#define ARG3   P.ops[P.size].arg3

#define ASSEMBLED asm_err = 0; goto assembled;
#define INVALID_ARG1 asm_err = INVALID_ARGS; invalArg = 1; goto assembled;
#define INVALID_ARG2 asm_err = INVALID_ARGS; invalArg = 2; goto assembled;
#define INVALID_ARG3 asm_err = INVALID_ARGS; invalArg = 3; goto assembled;

#define IS_REG(arg) ((arg && regNumber(arg) >= 0) ? REG : NONE)
#define REG_NUM(arg) regNumber(arg)
#define IS_NUM(arg, symtab) isArgNum(arg, NULL, symtab)
#define ARG_TO_NUM(arg, pnum, symtab) isArgNum(arg, pnum, symtab)
#define IS_LABEL(arg) isArgLabel(arg)

