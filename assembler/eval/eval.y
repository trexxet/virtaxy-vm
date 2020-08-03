%{
#include <stdio.h>
#include <stdint.h>
#include "errors.h"

extern int yylex();
void yyerror(YYSTYPE*, char*, const char*);

#define THROW_ERROR(errcode, arg) { \
	YYSTYPE err = *result = errcode; \
	yypcontext_t ctx = {yyssp, yytoken, &arg}; \
	yyreport_syntax_error(&ctx, &err, errStr); \
	YYABORT; }
%}

%define parse.error custom
%parse-param {YYSTYPE* result} {char* errStr}
%locations

%token T_NUM
%token T_ADD T_SUB T_MUL T_DIV
%token T_LPAR T_RPAR
%token T_UNKNOWN_SYMBOL

%left T_ADD T_SUB
%left T_MUL T_DIV
%precedence NEG

%start Eval

%%

Eval: Expr { *result = $1; }

Expr: T_NUM { $$ = $1; }
    | Expr T_ADD Expr { $$ = $1 + $3; }
    | Expr T_SUB Expr { $$ = $1 - $3; }
    | Expr T_MUL Expr { $$ = $1 * $3; }
    | Expr T_DIV Expr {
          if ($3 == 0) THROW_ERROR(EVAL_DIV_BY_ZERO, @2);
          $$ = $1 / $3;
      }
    | T_SUB Expr %prec NEG { $$ = -$2; }
    | T_LPAR Expr T_RPAR { $$ = $2; }
    | T_UNKNOWN_SYMBOL { THROW_ERROR(EVAL_UNKNOWN_SYMBOL, @1); }
    | error { THROW_ERROR(EVAL_INVALID_EXPRESSION, @1); }

%%


#define C_BOLD_RED "\033[1m\033[31m"
#define C_RESET "\033[0m"


int yyreport_syntax_error(const yypcontext_t* ctx, YYSTYPE* r, char* errStr) {
	if (!errStr) return 0;
	char* es = errStr;
	int hlStart = yypcontext_location(ctx)->first_column - 1;
	int hlEnd = yypcontext_location(ctx)->last_column - 1;
	// Print expression with bad token highlighted
	int i = 0;
	extern char* orig_expr;
	while (orig_expr[i]) {
		if (i == hlStart)
			es += sprintf(es, C_BOLD_RED);
		if (i == hlEnd)
			es += sprintf(es, C_RESET);
		es += sprintf(es, "%c", orig_expr[i]);
		i++;
	}
	es += sprintf(es, "\n");
	// Print cool arrow
	for (i = 1; i < hlStart + 1; i++)
		es += sprintf(es, " ");
	es += sprintf(es, C_BOLD_RED);
	for (i; i < hlEnd + 1; i++)
		es += sprintf(es, "^");
	sprintf(es, C_RESET);
	return 0;
}


void yyerror(YYSTYPE* r, char* errStr, char const *s) {
	sprintf(errStr, "Expression parse error: %s", s);
}

