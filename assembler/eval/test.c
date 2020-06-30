#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "eval.tab.h"

extern YYLTYPE yylloc;
extern int yy_scan_string(char *);
extern int yylex_destroy();


static char* expr = "0x3+4*2+1";


int main() {
	yy_scan_string(expr);
	YYSTYPE result = 0;
	yyparse(&result);
	yylex_destroy();
	printf("Result: %" YYSTYPE_PR "\n", result);
	return 0;
}


int yyerror(YYSTYPE* res, char const *s) {
	printf("%s\n", expr);
	for (int i = 0; i < yylloc.first_column - 1; i++) putchar(' ');
	printf("^\n");
	printf("%s\n", s);
}

