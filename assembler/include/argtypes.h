// Argument types & functions

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "symtable.h"
#include "../../common/generated/registers.h"


typedef enum {
	NONE = 0b00,
	NUM  = 0b01,
	REG  = 0b10
} argType;

#define argtypestr(arg) [arg] = #arg
const static char* argTypeStr[] = {
	argtypestr(NONE), 
	argtypestr(NUM), 
	argtypestr(REG)
};
#undef argtypestr

typedef struct {
	char *str;
	argType type;
} arg_t;


#define LOAD_ARG(arg)                   \
	arg.str = strtok(NULL, DELIM);  \
	arg.type = IS_NUM(arg.str, &S) | IS_REG(arg.str);

int isArgNum(char *arg, int64_t *num, symTable *S);
int isArgLabel(char *arg);
int regNumber(char* arg);

