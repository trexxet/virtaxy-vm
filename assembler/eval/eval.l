%{
#include "eval.tab.h"
#include "symtable.h"

#define YY_USER_ACTION {lex_update_yylloc();}
void lex_update_yylloc();
void lex_reset_state();

extern symTable S;
%}

%option noyywrap
%option noinput
%option nounput

symbol [a-zA-Z_\.][a-zA-Z0-9_\.]*

%%

[ \t]+              ;
[1-9][0-9]*         { yylval = strtoll(yytext, NULL, 10); return T_NUM; } /* Decimal number */
0[xX][0-9a-fA-F]+   { yylval = strtoll(yytext, NULL, 16); return T_NUM; } /* Hexadecimal prefix number */
[0-9a-fA-F]+[hH]    { yylval = strtoll(yytext, NULL, 16); return T_NUM; } /* Hexadecimal postfix number */
[0-1]+[bB]          { yylval = strtoll(yytext, NULL, 2); return T_NUM; } /* Binary number */
[0-7]+              { yylval = strtoll(yytext, NULL, 8); return T_NUM; } /* Octal number or zero */
"+"                 { return T_ADD; }
"-"                 { return T_SUB; }
"*"                 { return T_MUL; }
"/"                 { return T_DIV; }
"("                 { return T_LPAR; }
")"                 { return T_RPAR; }
{symbol}            {
                      YYSTYPE val = 0;
                      if (symGetValue(&S, yytext, &val) >= 0) { yylval = val; return T_NUM; }
                      else return *yytext;
                    }
.                   { return *yytext; }

%%

void lex_update_yylloc() {
	yylloc.first_column = yylloc.last_column;
	yylloc.last_column += yyleng;
}


void lex_reset_state() {
	yy_flush_buffer(YY_CURRENT_BUFFER);
	yylloc = (YYLTYPE){1, 1, 1, 1};
}

