#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "eval.tab.h"


YYSTYPE evalExpr(char *expr, int* err) {
	// Kinda ugly extern declarations - but Bison
	// does not provide them in header file
	extern void lex_reset_state();
	lex_reset_state();
	extern int yy_scan_string(char *);
	yy_scan_string(expr);
	extern char* tab_expr; // yyreport_syntax_error() does not know
	tab_expr = expr;       // about expr, so we pass it with extern
	YYSTYPE result = 0;
	*err = yyparse(&result);
	return result;
}


void evalPrintExpr(char *expr) {
	int err = 0;
	YYSTYPE result = evalExpr(expr, &err);
	if (!err) printf("%s = %" YYSTYPE_PR "\n", expr, result);
}


void die() {
	extern int yylex_destroy();
	yylex_destroy();
}


int main() {
	evalPrintExpr("0xA+0X1+bh+11b"); // 25
	evalPrintExpr("1 + 2 *  2"); // 5
	evalPrintExpr("2++3"); // unexpected +
	evalPrintExpr("1/(4-4)"); // div by 0
	die();
	return 0;
}

