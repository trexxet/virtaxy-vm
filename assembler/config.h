//Initialization configuration
#define DEFAULT_OUTPUT_FILENAME "a.vo"        // Default name of output file, if -o was not specified
#define SOURCE_STRING_LENGTH 127              // Max length of text string in source file
#define INIT_PROGRAM_SIZE 256                 // Initial program size in bytes

//Assembler configuration
#define DELIM " ,\t\n"                        // Delimiter with whitespaces
#define DELIM_IGN_WHSPC ",\n"                 // Delimiter without whitespaces
#define ERR_STR_LEN 128                       // Error explaining string length
#define CONST_KEYWORD "equ"                   // Keyword for defining constants
#define VAR_KEYWORD "var"                     // Keyword for initialized variables
#define RES_KEYWORD "res"                     // Keyword for reserved memory
#define COMMENT_CHR ';'                       // Character for commentaries
#define LABEL_CHR ':'                         // Character for labels
#define SYM_BLACKLIST_CHR "+-*/()"            // Characters symbol are forbidden to have

