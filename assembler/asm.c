#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define OPSIZE 4

#include "asm.h"
#include "errors.h"
#include "config.h"
#include "eval/eval.h"

// Symbol table types & functions
#include "symtable.h"
// Argument types & functions
#include "arg_type.h"
// Functions & macros for generated assembler code
#include "asm_gen.h"

#include "opcodes.h" // Generated


program P;
symTable S;


#include "assembler-encoder-gen.c" // Generated


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


// TODO: split function
__attribute__((hot))
errcode_t assembleString(char *sourceStr, int pass, char *errStr)
{
	arg_t arg[4] = { {.str = NULL, .type = NONE} };
	char *instrStr = arg[0].str = strtok(sourceStr, DELIM);
	if (!instrStr || instrStr[0] == COMMENT_CHR)
		return SUCCESS;

	// If label
	if (isArgLabel(instrStr))
	{
		char labelStr[SOURCE_STRING_LENGTH] = {0};
		strncpy(labelStr, instrStr, strlen(instrStr) - 1);
		if (symGetValue(&S, labelStr, NULL) < 0)
			symAdd(&S, labelStr, P.size);
		return SUCCESS;
	}

	loadArg(&arg[1], &S);
	if (arg[1].type != NONE)
		loadArg(&arg[2], &S);
	if (arg[2].type != NONE)
		loadArg(&arg[3], &S);

	// If keyword (constant, variable or reserved memory)
	if (arg[1].type == KEYWORD && IS_CORRECT_SYMBOL_NAME(instrStr) && arg[2].type == EXPR)
	{
		enum {CONST = 1, VAR = 2, RESMEM = 3};
		uint8_t symType = 0;
		if (strcmp(arg[1].str, CONST_KEYWORD) == 0)
			symType = CONST;
		else if (strcmp(arg[1].str, VAR_KEYWORD) == 0)
			symType = VAR;
		else if (strcmp(arg[1].str, RES_KEYWORD) == 0)
			symType = RESMEM;
		else goto notSymbol;

		int64_t value = 0;
		EVAL_EXPR(arg[2].str, &value, &S);
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
		#include "assembler-picker-gen.c" // Generated

		if (asm_err == UNKNOWN_COMMAND)
			sprintf(errStr, C_BOLD_RED"%s"C_RESET" %s, %s, %s",
			        instrStr, arg[1].str, arg[2].str, arg[3].str);

		if (asm_err == INVALID_ARGS)
		{
			// TODO: make use of invalArg
			// TODO: add expected types
			sprintf(errStr, "%s %s, %s, %s\n arg1: %s\n arg2: %s\n arg3: %s",
			        instrStr, arg[1].str, arg[2].str, arg[3].str,
		                argTypeStr[arg[1].type], argTypeStr[arg[2].type], argTypeStr[arg[3].type]);
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
	evalDie();
	free(P.bytes);
}

