//Command line configuration
#define COMMAND_LINE_OPTIONS "o:"             // Command line options for getopt()

//Initialization configuration
#define DEFAULT_OUTPUT_FILENAME "a.vo"        // Default name of output file, if -o was not specified
#define SOURCE_STRING_LENGTH 127              // Max length of text string in source file
#define INIT_PROGRAM_SIZE 128                 // Initial program size in bytes

//Assembling configuration
#define DELIM " ,\t\n"                        // Delim for strtok()
#define ERR_STR_LEN 128                       // Error explainning string length
#define CONST_KEYWORD "equ"                   // Keyword for defining constants
#define COMMENT_SYMBOL ';'                    // Symbol for comments
#define LABEL_SYMBOL ':'                      // Symbol for labels

