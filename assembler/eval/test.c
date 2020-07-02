#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "eval.tab.h"


static char* expr = NULL;


YYSTYPE evalExpr(char *expr, int* err) {
	extern int yy_scan_string(char *);
	extern void lex_reset_state();
	lex_reset_state();
	yy_scan_string(expr);
	YYSTYPE result = 0;
	*err = yyparse(&result);
	return result;
}


void evalPrintExpr(char *expr) {
	int err = 0;
	YYSTYPE result = evalExpr(expr, &err);
	if (!err) printf("%s = %" YYSTYPE_PR "\n", expr, result);
}


int main() {
	expr = "0x3+4*2+1";
	evalPrintExpr(expr);
	expr = "1 + 2";
	evalPrintExpr(expr);
	expr = "0xA + 2";
	evalPrintExpr(expr);
	extern int yylex_destroy();
	yylex_destroy();
	return 0;
}


int yyerror(YYSTYPE* res, char const *s) {
	extern YYLTYPE yylloc;
	printf("%s\n", expr);
	for (int i = 0; i < yylloc.first_column - 1; i++) putchar(' ');
	printf("^\n");
	printf("%s\n", s);
}

