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


__attribute__((hot))
int isArgLabel(char *arg)
{
	if (!arg)
		return 0;
	char *labelSymPtr = strrchr(arg, LABEL_SYMBOL);
	if (labelSymPtr && labelSymPtr == (strrchr(arg, 0) - 1))
		return 1;
	return 0;
}


__attribute__((hot))
int regNumber(char* arg) // Returns number of register arg or -1 if doesn't exists
{
	for (int64_t i = 0; i < NUM_OF_REGISTERS; i++)
		if ((strcmp(regTable[i].name, arg) == 0) && !regTable[i].private)
			return i;
	return -1;
}

