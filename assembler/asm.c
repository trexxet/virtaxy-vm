#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "asm.h"
#include "errors.h"
#include "config.h"

// Argument types & functions
#include "asm_arg.h"
// Register types & functions
#include "asm_reg.h"
// Macros for assembling
#include "asm_macros.h"

#include "generated/opcodes.h"


program P;
symTable S;


_ERRNO_T asmInit()
{
	P.size = 0;
	P.maxSize = INIT_PROGRAM_SIZE;
	return (P.ops = calloc(INIT_PROGRAM_SIZE, sizeof(instruction))) ? SUCCESS 
	                                                                : CANNOT_ALLOCATE_MEMORY;
}


__attribute__((hot))
_ERRNO_T assembleString(char *sourceStr, char *errStr)
{
	char *instrStr = strtok(sourceStr, DELIM);
	
	arg_t arg1, arg2;
	LOAD_ARG(arg1);
	LOAD_ARG(arg2);

	_ERRNO_T asm_err = UNKNOWN_COMMAND;
	int invalArg = 0;
	#include "generated/asm_generated.c"

assembled:
	P.size++; // Go to next command
	if (asm_err == UNKNOWN_COMMAND)
		sprintf(errStr, C_BOLD_RED"%s"C_RESET" %s, %s", instrStr, arg1.str, arg2.str);
	if (asm_err == INVALID_ARGS)
	{
		#define errStrWords instrStr, arg1.str, arg2.str, argTypeStr[arg1.type], argTypeStr[arg2.type]
		if (invalArg == 1)
			sprintf(errStr, 
			        "%s "C_BOLD_RED"%s"C_RESET", %s\n arg1: "C_BOLD_RED"%s"C_RESET"\n arg2: %s", 
			        errStrWords);
		if (invalArg == 2)
			sprintf(errStr, 
			        "%s %s, "C_BOLD_RED"%s"C_RESET"\n arg1: %s\n arg2: "C_BOLD_RED"%s"C_RESET, 
			        errStrWords);
	}
	return asm_err;
}

void asmFinal()
{
	free(P.ops);
}

