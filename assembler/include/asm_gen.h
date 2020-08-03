// Functions & macros for generated assembler code

#pragma once

#define CHECK_PROGRAM_SIZE(dSize) {                    \
	if (P.maxSize - P.size < dSize + 1)            \
		P.bytes = (int64_t *) realloc(P.bytes, \
			  (P.maxSize += P.maxSize / 2) * sizeof(int64_t)); }

#define INSTR_ENCODER(instr) _INSTR_##instr
#define DEF_INSTR_ENCODER(instr) int INSTR_ENCODER(instr) (arg_t arg[], errcode_t* asm_err)

#define OPCODE   P.bytes[P.size+0]
#define ARG(x)   P.bytes[P.size+x]

#define ASSEMBLED { *asm_err = 0; return 0; }
#define INVALID_ARG(n) { *asm_err = INVALID_ARGS; return n; }

#define REG_NUM(arg) regNumber(arg)
#define EVAL_EXPR(arg, pnum, symtab) argEvalExpr(arg, pnum, symtab, NULL, NULL)

