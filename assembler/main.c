#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "errors.h"
#include "config.h"

typedef struct {
	char *name[];
	uint8_t num;
} inputFileList_t;

struct {
	char *fileListNames[];
	FILE *openedFileHandle;
} dynAllocMem; //Dynamically allocated memory and other stuff to be cleared in finalization()

void parseCmdLineArgs(int argc, char *argv[], inputFileList_t *inputFileList, char *outputFilename);
void parseError(_ERRNO_T _errno, char *file, size_t line);
void finalization();

void main(int argc, char *argv[])
{
	_ERRNO_T _errno = asmInit(INIT_PROGRAM_SIZE);
	inputFileList_t inputFileList = {};
	char *outputFilename = DEFAULT_OUTPUT_FILENAME;
	parseCmdLineArgs(argc, argv, &inputFileList, outputFilename);

	for (uint16_t fileCounter = 0; fileCounter < inputFileList.num; fileCounter++)
	{
		char *fileName = inputFileList.name[fileCounter];
		dynAllocMem.openedFileHandle = fopen(fileName, "r");
		if (!dynAllocMem.openedFileHandle)
			parseError(CANNOT_OPEN_FILE, fileName, 0);
		if (feof(dynAllocMem.openedFileHandle))
			parseError(INPUT_IS_EMPTY, fileName, 0);
		char sourceString[SOURCE_STRING_LENGTH];
		size_t lineCounter = 0;
		while (fgets(sourceString, SOURCE_STRING_LENGTH, dynAllocMem.openedFileHandle) && (_errno == 0))
		{
			_errno = assembleString(sourceString);
			lineCounter++;
		}
		fclose(dynAllocMem.openedFileHandle);
		dynAllocMem.openedFileHandle = NULL;
		parseError(_errno, fileName, lineCounter);
	}
	finalization(SUCCESS);
}

void parseCmdLineArgs(int argc, char *argv[], inputFileList_t *inputFileList, char *outputFilename)
{
	int opt;
	opterr = 0;
	while ((opt = getopt(argc, argv, COMMAND_LINE_OPTIONS)) != -1)
		switch (opt)
		{
			case 'o':
				outputFilename = optarg;
				break;
			case '?':
				parseError(INCORRECT_COMMAND_LINE, NULL, 0);
				break;
		}
	inputFileList -> num = argc - optind;
	if (inputFileList -> num == 0)
		parseError(NO_INPUT_FILES, NULL, 0);
	dynAllocMem.fileListNames = inputFileList -> name = (char**) calloc(inputFileList -> num, sizeof(char*));
	for (int i = 0; i < inputFileList -> num; i++)
		inputFileList -> name[i] = argv[i + optind];
}

void parseError(_ERRNO_T _errno, char *file, size_t line)
{
	fprintf(stderr, "%s:%d: %s\n", file, line, errmsg[_errno]);
	if (_errno != SUCCESS)
		finalization(_errno);
}

_Noreturn void finalization(_ERRNO_T _errno)
{
	//Some stuff need fclose(), other need free(), so let's unite them with macro
	#define FREE(_FUNC_, _POINTER_)		\
	if (dynAllocMem._POINTER_) {		\
		_FUNC_(dynAllocMem._POINTER_);	\
		dynAllocMem._POINTER_ = NULL;	\
	}
	FREE(fclose, openedFileHandle);
	FREE(free, fileListNames);
	exit(_errno);
	#undef FREE
}
