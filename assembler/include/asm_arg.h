// Argument types & functions

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "symtable.h"


typedef enum {
	NONE = 0b0000,
	NUM  = 0b0001,
	REG  = 0b0010
} argType;

#define argtypestr(arg) [arg] = #arg
const char* argTypeStr[] = {
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


__attribute__((hot))
int isArgNum(char *arg, int64_t *num, symTable *S)
{
	if (!arg)
		return NONE;
	int64_t fake_num;
	int64_t *dest = num ? num : &fake_num;
	// Check if arg exists in symbol table
	if (symGetValue(S, arg, num ? num : NULL) >= 0)
		return NUM;
	// Check if arg is correct decimal / octal / hexadecimal beginning with '0x'
	char *endptr = arg;
	*dest = strtoll(arg, &endptr, 0);
	if (*endptr == 0)
		return NUM;
	// Check if arg ends with 'h'
	char argStrBuf[SOURCE_STRING_LENGTH] = {0};
	strcpy(argStrBuf, arg);
	int argStrBufLen = strlen(argStrBuf) - 1;
	if (argStrBuf[argStrBufLen] != 'h')
		return NONE;
	// Check if arg is correct hexadecimal ending with 'h'
	argStrBuf[argStrBufLen] = 0;
	endptr = argStrBuf;
	*dest = strtoll(argStrBuf, &endptr, 16);
	if (*endptr == 0)
		return NUM;
	return NONE;
}

#define IS_NUM(arg, symtab) isArgNum(arg, NULL, symtab)
#define ARG_TO_NUM(arg, pnum, symtab) isArgNum(arg, pnum, symtab)


__attribute__((hot))
int isArgLabel(char *arg)
{
	if (!arg)
		return 0;
	char *colonPtr = strrchr(arg, ':');
	if (colonPtr && colonPtr == (strrchr(arg, 0) - 1))
		return 1;
	return 0;
}

#define IS_LABEL(arg) isArgLabel(arg)

