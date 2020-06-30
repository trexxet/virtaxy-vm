#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "eval.tab.h"

extern int yy_scan_string(char *);
extern int yylex_destroy();


int main() {
	yy_scan_string("3+4*2+(-1)");
	YYSTYPE result = 0;
	yyparse(&result);
	yylex_destroy();
	printf("Result: %" YYSTYPE_PR "\n", result);
	return 0;
}


int yyerror(YYSTYPE* res, char const *s) {
	printf("%s\n", s);
}

