#define SOURCE_STRING_LENGTH 64 //Max length of text string in source file
#define INIT_PROGRAM_SIZE 128 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asm.h"

void finalization();
#define INCLUDE_IN_MAIN
#include "errors.h"
#undef INCLUDE_IN_MAIN
