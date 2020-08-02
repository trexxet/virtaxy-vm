#include <stdint.h>
#include "errors.h"

YYSTYPE evalExpr(char *expr, errcode_t* err);
void evalDie();

