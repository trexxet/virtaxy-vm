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
// Instruction type
#include "instr.h"
// Functions & macros for generated assembler code
#include "asm_gen.h"

#include "opcodes.h" // Generated


program P;
symTable S;


#include "asm_instr-gen.c" // Generated
const size_t instrCount = sizeof(instrTable) / sizeof(instr_t);


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


void loadArgs(arg_t arg[]) {
	// Expressions can have whitespaces, so we should avoid splitting them
	// Split w/o whitespaces if we have instruction line
	int delimNoWhitespace = (int) (getInstr(arg[0].str, instrTable, instrCount) != NULL);
	loadArg(&arg[1], delimNoWhitespace, &S);
	if (arg[1].type != NONE)
	{
		// Split w/o whitespaces if we have keyword
		if (arg[1].type == KEYWORD) delimNoWhitespace = 1;
		loadArg(&arg[2], delimNoWhitespace, &S);
	}
	if (arg[2].type != NONE)
		loadArg(&arg[3], delimNoWhitespace, &S);
}


void addSymLabel(const char* str) {
	char labelStr[SOURCE_STRING_LENGTH] = {0};
	// Cut label char
	strncpy(labelStr, str, strlen(str) - 1);
	if (symGetValue(&S, labelStr, NULL) < 0)
		symAdd(&S, labelStr, P.size);
}


int addSymKeyword(arg_t arg[])
{
	enum {CONST = 1, VAR = 2, RESMEM = 3};
	uint8_t symType = 0;
	if (strcmp(arg[1].str, CONST_KEYWORD) == 0)
		symType = CONST;
	else if (strcmp(arg[1].str, VAR_KEYWORD) == 0)
		symType = VAR;
	else if (strcmp(arg[1].str, RES_KEYWORD) == 0)
		symType = RESMEM;
	else return 0;

	int64_t value = 0;
	EVAL_EXPR(arg[2].str, &value, &S);
	if (symGetValue(&S, arg[0].str, NULL) < 0)
		symAdd(&S, arg[0].str, (symType == CONST) ? value : P.size);
	if (symType != CONST)
	{
		CHECK_PROGRAM_SIZE((symType == RESMEM) ? value : 1);
		if (symType == VAR)
			OPCODE = value;
		P.size += (symType == RESMEM) ? value : 1;
	}
	return 1;
}


errcode_t assembleInstruction(arg_t arg[], char* errStr)
{
	errcode_t asm_err = UNKNOWN_COMMAND;
	int invalArg = 0;
	instr_t *currInstr = getInstr(arg[0].str, instrTable, instrCount);
	if (currInstr)
		invalArg = currInstr->encoder(arg, &asm_err);

	if (asm_err == UNKNOWN_COMMAND)
		sprintf(errStr, C_BOLD_RED"%s"C_RESET" %s, %s, %s",
			arg[0].str, arg[1].str, arg[2].str, arg[3].str);

	if (asm_err == INVALID_ARGS)
	{
		// TODO: make use of invalArg
		// TODO: add expected types
		sprintf(errStr, "%s %s, %s, %s\n arg1: %s\n arg2: %s\n arg3: %s",
			arg[0].str, arg[1].str, arg[2].str, arg[3].str,
			argTypeStr[arg[1].type], argTypeStr[arg[2].type], argTypeStr[arg[3].type]);
	}
	return asm_err;
}


__attribute__((hot))
errcode_t assembleString(char *sourceStr, int pass, char *errStr)
{
	// Truncate commentary
	char* commentChar = strchr(sourceStr, COMMENT_CHR);
	if (commentChar) *commentChar = '\0';

	// Load first token
	arg_t arg[MAX_ARGS] = { {.str = NULL, .type = NONE} };
	char *instrStr = arg[0].str = strtok(sourceStr, DELIM);
	if (!instrStr) return SUCCESS;

	// If label
	if (isArgLabel(instrStr))
	{
		addSymLabel(instrStr);
		return SUCCESS;
	}

	loadArgs(arg);

	// If keyword (constant, variable or reserved memory)
	if (arg[1].type == KEYWORD && IS_CORRECT_SYMBOL_NAME(instrStr) && arg[2].type == EXPR)
		if (addSymKeyword(arg))
			return SUCCESS;

	// Try to assemble instruction on second pass
	errcode_t asm_err = 0;
	if (pass == 2)
		asm_err = assembleInstruction(arg, errStr);

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

