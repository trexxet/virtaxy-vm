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
	return (P->ops = calloc(INIT_PROGRAM_SIZE, sizeof(instruction))) ? SUCCESS 
	                                                                 : CANNOT_ALLOCATE_MEMORY;
}


// Argument types

typedef enum {
	NONE = 0,
	NUM,
	REG
} argType;

const char* argTypeStr[] = {"NONE", "NUM", "REG", "UNDEF"};

typedef struct {
	char *str;
	argType type;
} arg_t;


// Macros for assembling
#include "asm_macros.h"


// Functions for assembling


__attribute__((hot))
int isNum(char *arg)
{
	if (!arg)
		return 0;
	char *endptr = arg;
	strtoll(arg, &endptr, 0);
	if (*endptr == 0)
		return 1;
	char argStrBuf[SOURCE_STRING_LENGTH] = {0};
	strcpy(argStrBuf, arg);
	int argStrBufLen = strlen(argStrBuf) - 1;
	if (argStrBuf[argStrBufLen] != 'h')
		return 0;
	argStrBuf[argStrBufLen] = 0;
	endptr = argStrBuf;
	strtoll(argStrBuf, &endptr, 16);
	if (*endptr == 0)
		return 1;
	return 0;
}


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
	char *instrStr = strtok(sourceStr, DELIM);
	
	arg_t arg1, arg2;
	LOAD_ARG(arg1);
	LOAD_ARG(arg2);

	_ERRNO_T asm_err = UNKNOWN_COMMAND;
	int invalArg = 0;
	#include "generated/asm_generated.c"

assembled:
	P->size++;
	if (asm_err == UNKNOWN_COMMAND)
		sprintf(errStr, C_BOLD_RED"%s"C_RESET" %s, %s", instrStr, arg1.str, arg2.str);
	if (asm_err == INVALID_ARGS)
	{
		if (invalArg == 1)
			sprintf(errStr, "%s "C_BOLD_RED"%s"C_RESET
			        ", %s\n arg1: "C_BOLD_RED"%s"C_RESET"\n arg2: %s", 
			        instrStr, arg1.str, arg2.str, argTypeStr[arg1.type], argTypeStr[arg2.type]);
		if (invalArg == 2)
			sprintf(errStr, "%s %s, "C_BOLD_RED"%s"C_RESET
			        "\n arg1: %s\n arg2: "C_BOLD_RED"%s"C_RESET, 
			        instrStr, arg1.str, arg2.str, argTypeStr[arg1.type], argTypeStr[arg2.type]);
	}
	return asm_err;
}

