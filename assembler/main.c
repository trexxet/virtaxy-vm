#define _GNU_SOURCE
#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "errors.h"
#include "config.h"
#include "asm.h"


typedef struct {
	char *inputFilename;
	char *outputFilename;
} conf_t;


void parseCmdLineArgs(int argc, char *argv[], conf_t *conf);
void assembleFile(char *filename);
void writeProgram(char *filename);

void parseError(errcode_t errcode, char *file, size_t line, char *errStr);
void printVersion();
void printHelp();
void finalization();


void main(int argc, char *argv[])
{
	errcode_t errcode = asmInit();
	if (errcode)
		parseError(errcode, NULL, 0, NULL);

	conf_t conf = {NULL, DEFAULT_OUTPUT_FILENAME};
	parseCmdLineArgs(argc, argv, &conf);

	assembleFile(conf.inputFilename);
	writeProgram(conf.outputFilename);

	finalization(errcode);
}


void assembleFile(char *filename)
{
	FILE* openedFileHandle = fopen(filename, "r");
	if (!openedFileHandle)
		parseError(CANNOT_OPEN_FILE, filename, 0, NULL);
	if (feof(openedFileHandle))
		parseError(INPUT_IS_EMPTY, filename, 0, NULL);

	char sourceString[SOURCE_STRING_LENGTH + 1] = {0};
	size_t lineCounter = 0;
	char errStr[SOURCE_STRING_LENGTH + ERR_STR_LEN] = {0};
	extern program P;
	// At first pass, we only fill symbol table
	// Actual assembling is done at the second pass
	errcode_t errcode = SUCCESS;
	for (int pass = 1; pass <= 2; pass++)
	{
		while (fgets(sourceString, SOURCE_STRING_LENGTH, openedFileHandle) && errcode == SUCCESS)
		{
			if ((sourceString[0] != 0) && (sourceString[0] != '\n'))
				errcode = assembleString(sourceString, pass, errStr);
			lineCounter++;
		}
		if (pass == 1 && errcode == SUCCESS)
		{
			P.size = 0;
			lineCounter = 0;
			rewind(openedFileHandle);
		}
	}

	if (fclose(openedFileHandle) == EOF)
		parseError(CANNOT_CLOSE_FILE, filename, lineCounter, NULL);
	openedFileHandle = NULL;
	parseError(errcode, filename, lineCounter, errcode ? errStr : NULL);
}


void writeProgram(char *filename)
{
	extern program P;
	FILE* openedFileHandle = fopen(filename, "wb");
	if (!openedFileHandle)
		parseError(CANNOT_OPEN_FILE, filename, 0, NULL);
	for (uint64_t i = 0; i < P.size; i++)
		fwrite(&P.bytes[i], sizeof(uint64_t), 1, openedFileHandle);
	if (fclose(openedFileHandle) == EOF)
		parseError(CANNOT_CLOSE_FILE, filename, 0, NULL);
	openedFileHandle = NULL;
}


void parseCmdLineArgs(int argc, char *argv[], conf_t *conf)
{
	int opt;
	opterr = 0;
	extern int printSymtableAtFinal;
	while ((opt = getopt(argc, argv, "o:svh")) != -1)
		switch (opt)
		{
			case 'o': // Set output filename
				conf -> outputFilename = optarg;
				break;
			case 's': // Print symbol table
				printSymtableAtFinal = 1;
				break;
			case 'v': // Print version
				printVersion();
				finalization();
				break;
			case 'h': // Print help
				printHelp();
				finalization();
				break;
			default:
			case '?':
				parseError(INCORRECT_COMMAND_LINE, NULL, 0, NULL);
				break;
		}
	if (argc == optind)
		parseError(NO_INPUT_FILES, NULL, 0, NULL);
	conf -> inputFilename = argv[optind];
}


void parseError(errcode_t errcode, char *file, size_t line, char *errStr)
{
	fprintf((errcode == SUCCESS) ? stdout : stderr,
	                               "%s:%zu: %s\n", file, line, errmsg[errcode]);
	if (errStr)
		fprintf(stderr, "%s\n", errStr);
	if (errcode != SUCCESS)
		finalization(errcode);
}


void printVersion()
{
	printf("Virtaxy assembler version %s\n", VERSION);
	printf("Arch: %s\n", ARCH);
}


void printHelp()
{
	printVersion();
	printf("Options:\n");
	printf("\t-o=filename    Set output filename\n");
	printf("\t-s             Print symbol table at the end of assembling\n");
	printf("\t-v             Print version and arch\n");
	printf("\t-h             Print this help\n");
}


_Noreturn void finalization(errcode_t errcode)
{
	asmFinal();
	exit(errcode);
}

