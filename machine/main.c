#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "errors.h"
#include "machine.h"
#include "mem.h"


_ERRNO_T _errno = SUCCESS;


typedef struct {
	char *inputFilename;
	size_t memSize; 
} conf_t;


void parseCmdLineArgs(int argc, char *argv[], conf_t *conf);
void executeFile(char *filename);
void parseError(_ERRNO_T _errno, char *file, char *errStr);
void finalization();


void main(int argc, char* argv[])
{
	conf_t conf = {NULL, DEFAULT_MEMSIZE};
	parseCmdLineArgs(argc, argv, &conf);
	
	_errno = machineInit(conf.memSize);
	if (_errno)
		parseError(_errno, NULL, NULL);

	executeFile(conf.inputFilename);

	finalization();
}


void executeFile(char *filename)
{
	FILE* openedFileHandle = fopen(filename, "r");
	if (!openedFileHandle)
		parseError(CANNOT_OPEN_FILE, filename, NULL);
	if (feof(openedFileHandle))
		parseError(INPUT_IS_EMPTY, filename, NULL);
	
	extern mem_t M;
	int64_t *memPtr = M.data;
	while(fread(memPtr++, sizeof(int64_t), 1, openedFileHandle));
	_errno = machineRun();
	
	if (fclose(openedFileHandle) == EOF)
		parseError(CANNOT_CLOSE_FILE, filename, NULL);
	openedFileHandle = NULL;
	parseError(_errno, filename, NULL);
}


void parseCmdLineArgs(int argc, char *argv[], conf_t *conf)
{
	int opt;
	opterr = 0;
	extern int debug;
	while ((opt = getopt(argc, argv, COMMAND_LINE_OPTIONS)) != -1)
		switch (opt)
		{
			case 'm':
				conf -> memSize = strtol(optarg, NULL, 0);
				break;
			case 'd':
				debug = 1;
				break;
			case '?':
			default:
				parseError(INCORRECT_COMMAND_LINE, NULL, NULL);
				break;
		}
	if (argc == optind)
		parseError(NO_INPUT_FILES, NULL, NULL);
	conf -> inputFilename = argv[optind];
}


void parseError(_ERRNO_T _errno, char *file, char *errStr)
{
	fprintf((_errno == SUCCESS) ? stdout : stderr, "%s: %s\n", file, errmsg[_errno]);
	if (errStr)
		fprintf(stderr, "%s\n", errStr);
	if (_errno != SUCCESS)
		finalization();
}


//Here we free all dynamically allocated memory, pray the Valgrind
_Noreturn void finalization()
{
	machineDestroy();
	exit(_errno);
}

