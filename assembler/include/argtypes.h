// Argument types & functions

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "symtable.h"
#include "registers.h" // Generated


typedef enum {
	NONE    = 0b000,
	NUM     = 0b001,
	REG     = 0b010,
	KEYWORD = 0b100
} argType;

#define argtypestr(arg) [arg] = #arg
const static char* argTypeStr[] = {
	argtypestr(NONE), 
	argtypestr(NUM), 
	argtypestr(REG),
	argtypestr(KEYWORD)
};
#undef argtypestr

typedef struct {
	char *str;
	argType type;
} arg_t;


#define LOAD_ARG(arg) {                                           \
	arg.str = strtok(NULL, DELIM);                            \
	if (arg.str && arg.str[0] != COMMENT_SYMBOL)              \
		arg.type = IS_NUM(arg.str, &S) | IS_REG(arg.str) | IS_KEYWORD(arg.str); }

int isArgNum(char *arg, int64_t *num, symTable *S);
int isArgLabel(char *arg);
int isArgKeyword(char *arg);
int regNumber(char* arg);

