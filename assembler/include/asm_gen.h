// Functions & macros for generated assembler code

#pragma once

#define CHECK_PROGRAM_SIZE(dSize) {                    \
	if (P.maxSize - P.size < dSize + 1)            \
		P.bytes = (int64_t *) realloc(P.bytes, \
			  (P.maxSize += P.maxSize / 2) * sizeof(int64_t)); }

#define IF_INSTR(instr) if (strcmp(instrStr, #instr) == 0)

#define OPCODE   P.bytes[P.size+0]
#define ARG(x)   P.bytes[P.size+x]

#define ASSEMBLED { asm_err = 0; goto assembled; }
#define INVALID_ARG(x) { asm_err = INVALID_ARGS; invalArg = x; goto assembled; }

#define IS_REG(arg) ((arg && regNumber(arg) >= 0) ? REG : NONE)
#define REG_NUM(arg) regNumber(arg)
#define IS_EXPR(arg, symtab) isArgExpr(arg, NULL, symtab)
#define EVAL_EXPR(arg, pnum, symtab) isArgExpr(arg, pnum, symtab)
#define IS_LABEL(arg) isArgLabel(arg)
#define IS_KEYWORD(arg) isArgKeyword(arg)

