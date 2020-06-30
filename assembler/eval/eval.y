%{
#include <stdint.h>
extern int yyerror(YYSTYPE*, const char*);
extern int yylex();
%}

%define parse.error verbose
%parse-param {YYSTYPE* result}

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


