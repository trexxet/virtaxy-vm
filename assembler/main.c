#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "errors.h"
#include "config.h"
#include "include/asm.h"


typedef struct {
	uint16_t num;
	char name[MAX_INPUT_FILES][INPUT_FILENAME_MAX_LEN + 1];
} inputFilenames_t;


void parseCmdLineArgs(int argc, char *argv[], inputFilenames_t *inputFilenames, char *outputFilename);
void parseError(_ERRNO_T _errno, char *file, uint32_t line);
void finalization();


void main(int argc, char *argv[])
{
	_ERRNO_T _errno = asmInit();
	if (_errno)
		parseError(_errno, NULL, 0);
	inputFilenames_t inputFilenames = {};
	char *outputFilename = DEFAULT_OUTPUT_FILENAME;
	parseCmdLineArgs(argc, argv, &inputFilenames, outputFilename);

	for (uint16_t fileCounter = 0; fileCounter < inputFilenames.num; fileCounter++)
	{
		#define filename inputFilenames.name[fileCounter]
		FILE* openedFileHandle = fopen(filename, "r");
		if (!openedFileHandle)
			parseError(CANNOT_OPEN_FILE, filename, 0);
		if (feof(openedFileHandle))
			parseError(INPUT_IS_EMPTY, filename, 0);
		char sourceString[SOURCE_STRING_LENGTH];
		uint32_t lineCounter = 0;
		while (fgets(sourceString, SOURCE_STRING_LENGTH, openedFileHandle) && (_errno == 0))
		{
			_errno = assembleString(sourceString);
			lineCounter++;
		}
		if (fclose(openedFileHandle) == EOF)
			parseError(CANNOT_CLOSE_FILE, filename, lineCounter);
		openedFileHandle = NULL;
		parseError(_errno, filename, lineCounter);
		#undef filename
	}
	finalization(SUCCESS);
}


void parseCmdLineArgs(int argc, char *argv[], inputFilenames_t *inputFilenames, char *outputFilename)
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
	inputFilenames -> num = argc - optind;
	if (inputFilenames -> num == 0)
		parseError(NO_INPUT_FILES, NULL, 0);
	for (int i = 0; i < inputFilenames -> num; i++)
		strcpy(inputFilenames -> name[i], argv[optind + i]);
}


void parseError(_ERRNO_T _errno, char *file, uint32_t line)
{
	fprintf(stderr, "%s:%zu: %s\n", file, line, errmsg[_errno]);
	if (_errno != SUCCESS)
		finalization(_errno);
}


_Noreturn void finalization(_ERRNO_T _errno)
//Here we free all dynamically allocated memory, pray the Valgrind
{
	exit(_errno);
}

