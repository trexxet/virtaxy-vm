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

void parseCmdLineArgs(int argc, char *argv[], inputFileList_t *inputFileList, char *outputFilename);
void parseError(ERRNO_T _errno, char *file, size_t line);
void finalization();
