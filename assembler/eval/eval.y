%{
#include <stdio.h>
#include <stdint.h>
#include "eval_err.h"

extern int yylex();
void yyerror(YYSTYPE*, const char*);
int evalSilentParser = 0;
%}

%define parse.error custom
%parse-param {YYSTYPE* result}
%locations

%token T_NUM
%token T_ADD T_SUB T_MUL T_DIV
%token T_LPAR T_RPAR

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
          if ($3 == 0) {
              YYSTYPE err = *result = EVAL_ERR_DIV_BY_ZERO;
              yypcontext_t ctx = {yyssp, yytoken, &@2};
              yyreport_syntax_error(&ctx, &err);
              YYABORT;
          }
          $$ = $1 / $3;
      }
    | T_SUB Expr %prec NEG { $$ = -$2; }
    | T_LPAR Expr T_RPAR { $$ = $2; }

%%


#define C_BOLD_RED "\033[1m\033[31m"
#define C_RESET "\033[0m"


// As we're not interested in evaluation result in case of error, we
// may use it to report special error cases, such as division by 0 etc.
int yyreport_syntax_error(const yypcontext_t *ctx, YYSTYPE* err) {
	if (evalSilentParser) return 0;
	int pos = yypcontext_location(ctx)->first_column;
	extern char* orig_expr;

	int i = 0;
	while (orig_expr[i]) {
		if (i == pos - 1) fprintf(stderr, C_BOLD_RED"%c"C_RESET, orig_expr[i]);
		else fputc(orig_expr[i], stderr);
		i++;
	}
	fputc('\n', stderr);
	// Print cool arrow
	for (i = 1; i < pos; i++) fputc(' ', stderr);
	fprintf(stderr, C_BOLD_RED"^"C_RESET"\n");

	if (*err == EVAL_ERR_DIV_BY_ZERO)
		fprintf (stderr, C_BOLD_RED"error:"C_RESET" division by 0 in expression\n");
	else
		fprintf (stderr, C_BOLD_RED"error:"C_RESET" unexpected '%c' in expression\n",
		         orig_expr[pos-1]);
	return 0;
}


void yyerror(YYSTYPE* res, char const *s) {
	fprintf(stderr, "Expression parse error: %s\n", s);
}

