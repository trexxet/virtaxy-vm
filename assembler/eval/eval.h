#include <stdint.h>

extern int evalSilentParser;

YYSTYPE evalExpr(char *expr, int* err);
void evalDie();

