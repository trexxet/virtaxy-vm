%{
#include "eval.tab.h"
#define YY_USER_ACTION {update_yylloc();}
void update_yylloc();
%}

%option noyywrap
%option noinput
%option nounput

%%

[ \t]+        ;
[0-9]+        { yylval = strtoll(yytext, NULL, 0); return T_NUM; } /* Decimal or octal number */
"+"           { return T_ADD; }
"-"           { return T_SUB; }
"*"           { return T_MUL; }
"/"           { return T_DIV; }
"("           { return T_LPAR; }
")"           { return T_RPAR; }
.             { return *yytext; }

%%

void update_yylloc() {
	yylloc.first_column = yylloc.last_column;
	yylloc.last_column += yyleng;
}

