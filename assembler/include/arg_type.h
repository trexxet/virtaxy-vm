// Argument types & functions

#pragma once

#include <string.h>
#include <stdint.h>

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


void loadArg(arg_t *arg, int delimWithoutWhitespace, symTable *S);
int isArgExpr(char *arg, int64_t *num, symTable *S);
int isArgLabel(char *arg);
int isArgKeyword(char *arg);
int regNumber(char* arg);


#define IS_CORRECT_SYMBOL_NAME(arg) (strpbrk(arg, SYM_BLACKLIST_CHR) != arg)

