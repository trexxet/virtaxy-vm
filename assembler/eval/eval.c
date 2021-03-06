#include "eval.h"
#include "eval.tab.h"
#include "eval.lex.h"


// yyreport_syntax_error() does not know about expr, so we pass it with extern
char* orig_expr = NULL;


YYSTYPE evalExpr(char* expr, errcode_t* err, char* errStr) {
	yy_scan_string(expr);
	orig_expr = expr;
	YYSTYPE result = 0;
	*err = (errcode_t) yyparse(&result, errStr);
	orig_expr = NULL;
	extern void lex_reset_state();
	lex_reset_state();
	return result;
}


void evalDie() {
	orig_expr = NULL;
	yylex_destroy();
}

