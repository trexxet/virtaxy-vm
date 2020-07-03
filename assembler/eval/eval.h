#include <stdint.h>
#include "eval_err.h"

extern int evalSilentParser;

YYSTYPE evalExpr(char *expr, int* err);
void evalDie();

