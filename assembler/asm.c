#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "asm.h"
#include "errors.h"
#include "config.h"

// Symbol table types & functions
#include "symtable.h"
// Argument types & functions
#include "argtypes.h"
// Functions & macros for generated assembler code
#include "asm_gen.h"

#include "../../common/generated/opcodes.h"


program P;
symTable S;


_ERRNO_T asmInit()
{
	// Init program
	P.size = 0;
	P.maxSize = INIT_PROGRAM_SIZE;
	if (!(P.ops = calloc(INIT_PROGRAM_SIZE, sizeof(instruction))))
		return CANNOT_ALLOCATE_MEMORY;
	// Init symbol table
	return symInit(&S);
}


__attribute__((hot))
_ERRNO_T assembleString(char *sourceStr, int pass, char *errStr)
{
	char *instrStr = strtok(sourceStr, DELIM);
	
	// Check if label
	if (IS_LABEL(instrStr))
	{
		char labelStr[SOURCE_STRING_LENGTH] = {0};
		strncpy(labelStr, instrStr, strlen(instrStr) - 1);
		if (symGetValue(&S, labelStr, NULL) < 0)
			symAdd(&S, labelStr, P.size); 
		return SUCCESS;
	}

	arg_t arg1, arg2, arg3;
	LOAD_ARG(arg1);
	LOAD_ARG(arg2);
	LOAD_ARG(arg3);

	// Check if new constant
	if ((strcmp(arg1.str, CONST_KEYWORD) == 0) && IS_NUM(arg2.str, &S))
	{
		int64_t value = 0;
		ARG_TO_NUM(arg2.str, &value, &S);
		if (symGetValue(&S, instrStr, NULL) < 0)
			symAdd(&S, instrStr, value);
		return SUCCESS;
	}

	// Try to assemble command on second pass
	_ERRNO_T asm_err = 0;
	if (pass == 2)
	{
		asm_err = UNKNOWN_COMMAND;
		int invalArg = 0;
		#include "asm_generated.c"

		assembled:

		if (asm_err == UNKNOWN_COMMAND)
			sprintf(errStr, C_BOLD_RED"%s"C_RESET" %s, %s", instrStr, arg1.str, arg2.str, arg3.str);

		if (asm_err == INVALID_ARGS)
		{
			#define errStrWords instrStr, arg1.str, arg2.str, arg3.str, \
			                    argTypeStr[arg1.type], argTypeStr[arg2.type], argTypeStr[arg3.type]
				sprintf(errStr, 
					"%s %s, %s, %s\n arg1: %s\n arg2: %s\n, arg3: %s", 
					errStrWords);
			#undef errStrWords
		}
	}

	P.size++; // Go to next command
	return asm_err;
}


void asmFinal()
{
	symPrint(&S);
	symDestroy(&S);
	free(P.ops);
}

