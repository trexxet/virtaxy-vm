%{
#include "eval.tab.h"
%}

%option noyywrap

%%

[ \t]+      ;
[0-9]+      { yylval = strtoll(yytext, NULL, 0); return T_NUM; }
"+"         { return T_ADD; }
"-"         { return T_SUB; }
"*"         { return T_MUL; }
"/"         { return T_DIV; }
"("         { return T_LPAR; }
")"         { return T_RPAR; }

%%

