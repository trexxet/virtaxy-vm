%{
#include "eval.tab.h"
#define YY_USER_ACTION {lex_update_yylloc();}
void lex_update_yylloc();
void lex_reset_state();
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

void lex_update_yylloc() {
	yylloc.first_column = yylloc.last_column;
	yylloc.last_column += yyleng;
}


void lex_reset_state() {
	yy_flush_buffer(YY_CURRENT_BUFFER);
	yylloc = (YYLTYPE){1, 1, 1, 1};
	extern char* tab_expr;
	tab_expr = NULL;
}

