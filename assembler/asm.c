#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "asm.h"
#include "errors.h"
#include "config.h"

#include "generated/opcodes.h"


_ERRNO_T asmInit(program *P)
{
	P->size = 0;
	P->maxSize = INIT_PROGRAM_SIZE;
	return (P->ops = calloc(INIT_PROGRAM_SIZE, sizeof(int64_t))) ? SUCCESS 
	                                                             : CANNOT_ALLOCATE_MEMORY;
}


// Argument types

typedef enum {
	NONE = 0,
	NUM,
	REG
} argType;

const char* argTypeStr[] = {"NONE", "NUM", "REG"};

typedef struct {
	char *str;
	argType type;
} arg_t;


// Macros for assembling

#define LOAD_ARG(arg)                   \
	arg.str = strtok(NULL, DELIM);  \
	arg.type = IS_NUM(arg.str) + IS_REG(arg.str) * 2;

#define CHECK_PROGRAM_SIZE(incsize)                          \
	if (P->maxSize - P->size < incsize)                  \
		P->ops = (int64_t *) realloc(P->ops,         \
			   (P->maxSize += P->maxSize * 2) * sizeof(int64_t))

#define IF_INSTR(instr) if (strcmp(instruction, #instr) == 0)

#define NEXT_COMMAND P->ops[P->size++]

#define IS_REG2(arg) (arg && strlen(arg) == 2 &&          \
		      strchr(REGISTER_POSTFIX, arg[1]) && \
		      strchr(REGISTER_LETTER, arg[0]))

#define IS_REG3(arg) (arg && strlen(arg) == 3 &&         \
		      arg[2] == REGISTER_POSTFIX[0] &&   \
		      strchr(REGISTER_PREFIX, arg[0]) && \
		      strchr(REGISTER_LETTER, arg[1]))

#define IS_REG(arg) (IS_REG2(arg) || IS_REG3(arg))

#define REG_NUM(arg) registerNumber(arg)

#define IS_NUM(arg) (arg && strspn(arg, "0123456789") == strlen(arg))


// Functions for assembling


__attribute__((hot))
int registerNumber(char* arg)  // Returns number of register arg,
{                              // or 0 if arg isn't a register.
	#define _getPos(_STR_, _CHR_) (strchr(_STR_, _CHR_) - _STR_)
	if (!arg)              // ate NULL
		return 0;

	if (IS_REG2(arg))      // 2-letter register name (without prefix)
		return 	_getPos(REGISTER_LETTER, arg[0]) * NUM_OF_REGS_IN_GROUP +
		        strlen(REGISTER_PREFIX) + _getPos(REGISTER_POSTFIX, arg[1]) + 1;

	if (IS_REG3(arg))      // 3-letter register name (without postfix)
		return _getPos(REGISTER_LETTER, arg[1]) * NUM_OF_REGS_IN_GROUP +
		       _getPos(REGISTER_PREFIX, arg[0]) + 1;

	#undef _getPos
	return 0;
}


__attribute__((hot))
_ERRNO_T assembleString(char *sourceStr, program *P, char *errStr)
{
	char *instruction = strtok(sourceStr, DELIM);
	
	arg_t arg1, arg2;
	LOAD_ARG(arg1);
	LOAD_ARG(arg2);

	_ERRNO_T asm_err = UNKNOWN_COMMAND;
	#include "generated/asm_generated.c"
assemblied:
	if (asm_err)
	{
		if (asm_err == UNKNOWN_COMMAND)
			sprintf(errStr, C_BOLD_RED"%s"C_RESET" %s, %s", instruction, 
			                                                arg1.str, arg2.str);
		if (asm_err == INVALID_ARGS)
			sprintf(errStr, "%s %s, %s\n arg1: %s\n arg2: %s", instruction,
			                                                   arg1.str, arg2.str,
			                                                   argTypeStr[arg1.type],
			                                                   argTypeStr[arg2.type]);		
		return asm_err;
	}

	return 0;
}

