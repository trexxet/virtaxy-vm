// Argument types & functions

#pragma once

#include <stdlib.h>


typedef enum {
	NONE = 0,
	NUM,
	REG
} argType;

const char* argTypeStr[] = {"NONE", "NUM", "REG", "UNDEF"};

typedef struct {
	char *str;
	argType type;
} arg_t;


#define LOAD_ARG(arg)                   \
	arg.str = strtok(NULL, DELIM);  \
	arg.type = IS_NUM(arg.str) + IS_REG(arg.str) * 2;


__attribute__((hot))
int isArgNum(char *arg)
{
	if (!arg)
		return 0;
	char *endptr = arg;
	strtoll(arg, &endptr, 0);
	if (*endptr == 0)
		return 1;
	char argStrBuf[SOURCE_STRING_LENGTH] = {0};
	strcpy(argStrBuf, arg);
	int argStrBufLen = strlen(argStrBuf) - 1;
	if (argStrBuf[argStrBufLen] != 'h')
		return 0;
	argStrBuf[argStrBufLen] = 0;
	endptr = argStrBuf;
	strtoll(argStrBuf, &endptr, 16);
	if (*endptr == 0)
		return 1;
	return 0;
}

#define IS_NUM(arg) isArgNum(arg)

