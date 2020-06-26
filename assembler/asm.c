#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define OPSIZE 4

#include "asm.h"
#include "errors.h"
#include "config.h"

// Symbol table types & functions
#include "symtable.h"
// Argument types & functions
#include "argtypes.h"
// Functions & macros for generated assembler code
#include "asm_gen.h"

#include "opcodes.h" // Generated


program P;
symTable S;


int printSymtableAtFinal = 0;


errcode_t asmInit()
{
	// Init program
	P.size = 0;
	P.maxSize = INIT_PROGRAM_SIZE;
	if (!(P.bytes = calloc(INIT_PROGRAM_SIZE, sizeof(int64_t))))
		return CANNOT_ALLOCATE_MEMORY;
	// Init symbol table
	return symInit(&S);
}


__attribute__((hot))
errcode_t assembleString(char *sourceStr, int pass, char *errStr)
{
	char *instrStr = strtok(sourceStr, DELIM);
	if (!instrStr || instrStr[0] == COMMENT_SYMBOL)
		return SUCCESS;
	
	// If label
	if (IS_LABEL(instrStr))
	{
		char labelStr[SOURCE_STRING_LENGTH] = {0};
		strncpy(labelStr, instrStr, strlen(instrStr) - 1);
		if (symGetValue(&S, labelStr, NULL) < 0)
			symAdd(&S, labelStr, P.size); 
		return SUCCESS;
	}

	arg_t arg1 = {NULL, NONE}, arg2 = {NULL, NONE}, arg3 = {NULL, NONE};
	LOAD_ARG(arg1);
	if (arg1.type != NONE)
		LOAD_ARG(arg2);
	if (arg2.type != NONE)
		LOAD_ARG(arg3);

	// If keyword (constant, variable or reserved memory)
	if (arg1.type == KEYWORD && IS_NUM(arg2.str, &S))
	{
		enum {CONST = 1, VAR = 2, RESMEM = 3};
		uint8_t symType = 0;
		if (strcmp(arg1.str, CONST_KEYWORD) == 0)
			symType = CONST;
		else if (strcmp(arg1.str, VAR_KEYWORD) == 0)
			symType = VAR;
		else if (strcmp(arg1.str, RES_KEYWORD) == 0)
			symType = RESMEM;
		else goto notSymbol;

		int64_t value = 0;
		ARG_TO_NUM(arg2.str, &value, &S);
		if (symGetValue(&S, instrStr, NULL) < 0)
			symAdd(&S, instrStr, (symType == CONST) ? value : P.size);
		if (symType != CONST)
		{
			CHECK_PROGRAM_SIZE((symType == RESMEM) ? value : 1);
			if (symType == VAR)
				OPCODE = value;
			P.size += (symType == RESMEM) ? value : 1;
		}
		return SUCCESS;
	}
	notSymbol: ;

	// Try to assemble command on second pass
	errcode_t asm_err = 0;
	if (pass == 2)
	{
		asm_err = UNKNOWN_COMMAND;
		int invalArg = 0;
		#include "assembler-gen.c" // Generated

		assembled:

		if (asm_err == UNKNOWN_COMMAND)
			sprintf(errStr, C_BOLD_RED"%s"C_RESET" %s, %s", instrStr, arg1.str, arg2.str, arg3.str);

		if (asm_err == INVALID_ARGS)
		{
			#define errStrWords instrStr, arg1.str, arg2.str, arg3.str, \
			                    argTypeStr[arg1.type], argTypeStr[arg2.type], argTypeStr[arg3.type]
				sprintf(errStr, 
					"%s %s, %s, %s\n arg1: %s\n arg2: %s\n arg3: %s", 
					errStrWords);
			#undef errStrWords
		}
	}

	P.size += OPSIZE;
	return asm_err;
}


void asmFinal()
{
	if (printSymtableAtFinal)
		symPrint(&S);
	symDestroy(&S);
	free(P.bytes);
}

