#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "arg_type.h"
#include "eval/eval.h"


__attribute__((hot))
void loadArg(arg_t* arg, int delimWithoutWhitespace, symTable* S)
{
	arg->str = strtok(NULL, delimWithoutWhitespace ? DELIM_IGN_WHSPC : DELIM);
	if (arg->str)
	{
		// Strip whitespaces
		while (isspace(*arg->str)) arg->str++;
		char* end = strrchr(arg->str, '\0');
		while (isspace(*--end));
		end[1] = '\0';

		int parseErr = 0;
		// Set arg type
		// Expression check should be done last, as everything that
		// is not instruction, register or keyword is an expression
		arg->type = ((regNumber(arg->str) >= 0) ? REG : NONE) | isArgKeyword(arg->str);
		if (!arg->type)
			arg->type = argEvalExpr(arg->str, NULL, S, &parseErr);
	}
}


__attribute__((hot))
int argEvalExpr(char* arg, YYSTYPE* num, symTable* S, int* err)
{
	if (!arg)
		return NONE;
	int parseErr = 0;
	YYSTYPE result = 0;
	YYSTYPE* pr = num ? num : &result;
	// To check only, run parser in silent mode
	evalSilentParser = (int) (num == NULL);
	*pr = evalExpr(arg, &parseErr);
	if (err && parseErr)
		*err = *pr;
	return EXPR;
}


__attribute__((hot))
int isArgLabel(char* arg)
{
	if (!arg || !IS_CORRECT_SYMBOL_NAME(arg))
		return 0;
	char *labelSymPtr = strrchr(arg, LABEL_CHR);
	if (labelSymPtr && labelSymPtr == (strrchr(arg, 0) - 1))
		return 1;
	return 0;
}


__attribute__((hot))
int isArgKeyword(char* arg)
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

