#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "argtypes.h"


__attribute__((hot))
int isArgNum(char *arg, int64_t *num, symTable *S)
{
	if (!arg)
		return NONE;
	int64_t fake_num;
	int64_t *dest = num ? num : &fake_num;
	// Check if arg exists in symbol table
	if (IS_CORRECT_SYMBOL_NAME(arg) && symGetValue(S, arg, num) >= 0)
		return EXPR;
	// Check if arg is correct decimal / octal / hexadecimal beginning with '0x'
	char *endptr = arg;
	*dest = strtoll(arg, &endptr, 0);
	if (*endptr == 0)
		return EXPR;
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
		return EXPR;
	return NONE;
}


__attribute__((hot))
int isArgLabel(char *arg)
{
	if (!arg || !IS_CORRECT_SYMBOL_NAME(arg))
		return 0;
	char *labelSymPtr = strrchr(arg, LABEL_CHR);
	if (labelSymPtr && labelSymPtr == (strrchr(arg, 0) - 1))
		return 1;
	return 0;
}


__attribute__((hot))
int isArgKeyword(char *arg)
{
	if (!arg)
		return 0;
	#define _strcmp(_kword) (strcmp(arg, _kword) == 0)
	if (_strcmp(CONST_KEYWORD) || _strcmp(VAR_KEYWORD) || _strcmp(RES_KEYWORD))
		return KEYWORD;
	#undef _strcmp
	return 0;
}


__attribute__((hot))
int regNumber(char* arg) // Returns number of register arg or -1 if doesn't exists
{
	for (int64_t i = 0; i < NUM_OF_REGNAMES; i++)
		if ((strcmp(regTable[i].name, arg) == 0) && !regTable[i].private)
			return i;
	return -1;
}

