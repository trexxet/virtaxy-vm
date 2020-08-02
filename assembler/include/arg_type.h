// Argument types & functions

#pragma once

#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "symtable.h"
#include "registers.h" // Generated


typedef enum {
	NONE    = 0b000,
	EXPR    = 0b001,
	REG     = 0b010,
	KEYWORD = 0b100
} argType;

#define argtypestr(arg) [arg] = #arg
const static char* argTypeStr[] = {
	argtypestr(NONE),
	argtypestr(EXPR),
	argtypestr(REG),
	argtypestr(KEYWORD)
};
#undef argtypestr


typedef struct {
	char *str;
	argType type;
} arg_t;

#define MAX_ARGS 3+1


errcode_t loadArg(arg_t* arg, int delimWithoutWhitespace, symTable* S);
int argEvalExpr(char* arg, YYSTYPE* num, symTable* S, errcode_t *err);
int isArgLabel(const char* arg);
int isArgKeyword(const char* arg);
int isArgRegister(const char* arg);
int regNumber(const char* arg);

