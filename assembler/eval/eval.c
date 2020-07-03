#include "eval.h"
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


void evalDie() {
	extern int yylex_destroy();
	yylex_destroy();
}

