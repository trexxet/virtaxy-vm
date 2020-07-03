#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "eval.h"


void evalPrintExpr(char *expr) {
	int err = 0;
	YYSTYPE result = evalExpr(expr, &err);
	if (!err) printf("%s = %" YYSTYPE_PR "\n", expr, result);
}


int main() {
	evalPrintExpr("0xA+0X1+bh+11b"); // 25
	evalPrintExpr("1 + 2 *  2"); // 5
	evalPrintExpr("2++3"); // unexpected +
	evalPrintExpr("1/(4-4)"); // div by 0
	evalDie();
	return 0;
}

