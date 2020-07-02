%{
#include <stdio.h>
#include <stdint.h>
extern int yylex();
void yyerror(YYSTYPE*, const char*);
char *tab_expr = NULL;
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
    | Expr T_DIV Expr { $$ = $1 / $3; }
    | T_SUB Expr %prec NEG { $$ = -$2; }
    | T_LPAR Expr T_RPAR { $$ = $2; }

%%


#define C_BOLD_RED "\033[1m\033[31m"
#define C_RESET "\033[0m"


int yyreport_syntax_error(const yypcontext_t *ctx, YYSTYPE* res) {
	int pos = yypcontext_location(ctx)->first_column;
	const char* token = yysymbol_name(yypcontext_token(ctx));

	int i = 0;
	while (tab_expr[i]) {
		if (i == pos - 1) fprintf(stderr, C_BOLD_RED"%c"C_RESET, tab_expr[i]);
		else fputc(tab_expr[i], stderr);
		i++;
	}
	fputc('\n', stderr);
	// Print cool arrow
	for (i = 1; i < pos; i++) fputc(' ', stderr);
	fprintf(stderr, C_BOLD_RED"^"C_RESET"\n");

	fprintf (stderr, "Syntax error in expression: unexpected token %s\n", token);
	return 0;
}


void yyerror(YYSTYPE* res, char const *s) {
	fprintf(stderr, "Expression parse error: %s\n", s);
}

