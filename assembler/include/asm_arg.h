// Argument types & functions

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


typedef enum {
	NONE = 0,
	NUM,
	REG,
	LABEL
} argType;

const char* argTypeStr[] = {"NONE", "NUM", "REG", "LABEL"};

typedef struct {
	char *str;
	argType type;
} arg_t;


#define LOAD_ARG(arg)                   \
	arg.str = strtok(NULL, DELIM);  \
	arg.type = IS_NUM(arg.str, NULL) | IS_REG(arg.str) | IS_LABEL(arg.str);


__attribute__((hot))
int isArgNum(char *arg, int64_t *num)
{
	if (!arg)
		return NONE;
	// Check if arg is correct decimal / octal /  hexadecimal beginning with '0x'
	char *endptr = arg;
	if (num)
		*num = strtoll(arg, &endptr, 0);
	else
		strtoll(arg, &endptr, 0);
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
	if (num)
		*num = strtoll(argStrBuf, &endptr, 16);
	else
		strtoll(argStrBuf, &endptr, 16);
	if (*endptr == 0)
		return NUM;
	return NONE;
}

#define IS_NUM(arg, pnum) isArgNum(arg, pnum)


__attribute__((hot))
int isArgReg(char *arg)
{
	if (!arg)
		return NONE;
	// Check if arg is 2-letter register
	if (strlen(arg) == 2 &&
	    strchr(REGISTER_POSTFIX, arg[1]) &&
	    strchr(REGISTER_LETTER, arg[0]))
		return REG;
	// Check if arg is 3-letter register
	if (strlen(arg) == 3 &&
	    arg[2] == REGISTER_POSTFIX[0] &&
	    strchr(REGISTER_PREFIX, arg[0]) &&
	    strchr(REGISTER_LETTER, arg[1]))
		return REG;
	return NONE;
}

#define IS_REG(arg) isArgReg(arg)


__attribute__((hot))
int isArgLabel(char *arg)
{
	if (!arg)
		return NONE;
	char *colonPtr = strrchr(arg, ':');
	if (colonPtr && colonPtr == (strrchr(arg, 0) - 1))
		return LABEL;
	return NONE;
}

#define IS_LABEL(arg) isArgLabel(arg)

