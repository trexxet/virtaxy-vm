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


errcode_t loadArgs(arg_t arg[], char* errStr) {
	// Expressions can have whitespaces, so we should avoid splitting them
	// Split w/o whitespaces if we have instruction line
	int delimNoWhitespace = isInstr(arg[0].str, instrTable, instrCount);
	errcode_t err = loadArg(&arg[1], delimNoWhitespace, &S, errStr);
	if (arg[1].type != NONE && !err)
	{
		// Split w/o whitespaces if we have keyword
		if (arg[1].type == KEYWORD) delimNoWhitespace = 1;
		err = loadArg(&arg[2], delimNoWhitespace, &S, errStr);
	}
	if (arg[2].type != NONE && !err)
		err = loadArg(&arg[3], delimNoWhitespace, &S, errStr);
	return err;
}


void addSymLabel(const char* str) {
	char labelStr[SOURCE_STRING_LENGTH] = {0};
	// Cut label char
	strncpy(labelStr, str, strlen(str) - 1);
	if (symGetValue(&S, labelStr, NULL) < 0)
		symAdd(&S, labelStr, P.size);
}


int addSymKeyword(arg_t arg[], char* errStr)
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

	YYSTYPE value = 0;
	argEvalExpr(arg[2].str, &value, &S, NULL, errStr);
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
	instr_t* currInstr = getInstr(arg[0].str, instrTable, instrCount);
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
errcode_t assembleString(char* sourceStr, int pass, char* errStr)
{
	// Truncate commentary
	char* commentChar = strchr(sourceStr, COMMENT_CHR);
	if (commentChar) *commentChar = '\0';

	// Load first token
	arg_t arg[MAX_ARGS] = { {.str = NULL, .type = NONE} };
	char* instrStr = arg[0].str = strtok(sourceStr, DELIM);
	if (!instrStr) return SUCCESS;

	// If label
	if (isArgLabel(instrStr))
	{
		addSymLabel(instrStr);
		return SUCCESS;
	}

	errcode_t asm_err = loadArgs(arg, errStr);
	// Ignore unknown symbols on first pass
	if (pass == 1 && asm_err == EVAL_UNKNOWN_SYMBOL)
		asm_err = SUCCESS;
	if (asm_err)
		return asm_err;

	// If keyword (constant, variable or reserved memory)
	if (arg[1].type == KEYWORD && IS_CORRECT_SYMBOL_NAME(instrStr) && arg[2].type == EXPR)
		if (addSymKeyword(arg, errStr))
			return SUCCESS;

	// Try to assemble instruction on second pass
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

