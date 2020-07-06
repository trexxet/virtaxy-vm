#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "arg_type.h"
#include "eval/eval.h"


__attribute__((hot))
void loadArg(arg_t *arg, symTable *S)
{
	arg->str = strtok(NULL, DELIM);
	if (arg->str && arg->str[0] != COMMENT_CHR)
		arg->type = isArgExpr(arg->str, NULL, S)
			  | ((arg && regNumber(arg->str) >= 0) ? REG : NONE)
			  | isArgKeyword(arg->str);
}


__attribute__((hot))
int isArgExpr(char *arg, int64_t *num, symTable *S)
{
	if (!arg)
		return NONE;
	// Check if arg exists in symbol table and fetch if needed
	if (IS_CORRECT_SYMBOL_NAME(arg) && symGetValue(S, arg, num) >= 0)
		return EXPR;

	int parseErr = 0;
	// To check only, run parser in silent mode
	if (!num) {
		evalSilentParser = 1;
		YYSTYPE result = evalExpr(arg, &parseErr);
		if (parseErr && result != EVAL_ERR_DIV_BY_ZERO)
			return NONE;
		return EXPR;
	}
	evalSilentParser = 0;
	*num = evalExpr(arg, &parseErr);
	if (parseErr && *num != EVAL_ERR_DIV_BY_ZERO)
		return NONE;
	return EXPR;
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

