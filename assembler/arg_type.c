#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "arg_type.h"
#include "eval/eval.h"


__attribute__((hot))
errcode_t loadArg(arg_t* arg, int delimWithoutWhitespace, symTable* S)
{
	arg->str = strtok(NULL, delimWithoutWhitespace ? DELIM_IGN_WHSPC : DELIM);
	errcode_t parseErr = 0;
	if (arg->str)
	{
		// Strip whitespaces
		while (isspace(*arg->str)) arg->str++;
		char* end = strrchr(arg->str, '\0');
		while (isspace(*--end));
		end[1] = '\0';

		// Set arg type
		// Expression check should be done last, as everything that
		// is not instruction, register or keyword is an expression
		arg->type = isArgRegister(arg->str) | isArgKeyword(arg->str);
		if (!arg->type)
			arg->type = argEvalExpr(arg->str, NULL, S, &parseErr);
	}
	return parseErr;
}


__attribute__((hot))
int argEvalExpr(char* arg, YYSTYPE* num, symTable* S, errcode_t* err)
{
	if (!arg)
		return NONE;
	errcode_t parseErr = 0;
	YYSTYPE result = 0;
	YYSTYPE* pr = num ? num : &result;
	*pr = evalExpr(arg, &parseErr);
	if (err && parseErr)
		*err = *pr;
	return EXPR;
}


__attribute__((hot))
int isArgLabel(const char* arg)
{
	if (!arg || !IS_CORRECT_SYMBOL_NAME(arg))
		return 0;
	char *labelSymPtr = strrchr(arg, LABEL_CHR);
	if (labelSymPtr && labelSymPtr == (strrchr(arg, 0) - 1))
		return 1;
	return 0;
}


__attribute__((hot))
int isArgKeyword(const char* arg)
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
int regNumber(const char* arg) // Returns number of register arg or -1 if doesn't exists
{
	for (int64_t i = 0; i < NUM_OF_REGNAMES; i++)
		if ((strcmp(regTable[i].name, arg) == 0) && !regTable[i].private)
			return i;
	return -1;
}


__attribute__((hot))
int isArgRegister(const char* arg)
{
	return (regNumber(arg) >= 0) ? REG : NONE;
}

