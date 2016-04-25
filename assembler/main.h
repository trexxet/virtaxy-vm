#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "asm.h"

typedef struct {
	char *name[];
	uint8_t num;
} inputFileList_t;

struct {
	char *fileListNames[];
	FILE *openedFileHandle;
} dynAllocMem; //Dynamically allocated memory and other stuff to be cleared in finalization()

void parseCommandLineArguments(int argc, char *argv[], inputFileList_t *inputFileList, char *outputFilename);
void finalization();
#define INCLUDE_IN_MAIN
#include "errors.h"
#undef INCLUDE_IN_MAIN
