#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include <stdbool.h>
#include <getopt.h>

#define FORMAT_LENGTH 5
#define FILENAME_LENGTH 20
#define NUM_ROWS_DEFAULT 5
#define NUM_COLS_DEFAULT 5
#define USAGE "\
Usage: %s [--help] [--num-rows VALUE] [--num-cols VALUE]\n\
    [--output-format STRING] [--output-filename FILENAME]\n\
\n\
Generates a random maze on the square grid.\n\
\n\
Optional arguments:\n\
  --help                   Show this help message and exit\n\
  --num-rows VALUE         The number of rows in the maze.\n\
                           The default value is 5.\n\
  --num-cols VALUE         The number of columns in the maze.\n\
                           The default value is 5.\n\
  --output-format STRING   Selects the ouput format (either \"text\" or \"png\").\n\
                           The default format is \"text\".\n\
  --output-filename STRING The name of the output file.\n\
                           Mandatory for png format.\n\
                           If not specified, displays on stdout.\n\
"

// Parsing errors
enum Error {
    TP3_OK = 0,
    TP3_ERROR_TOO_MANY_ARGUMENTS = 1,
    TP3_ERROR_FORMAT_NOT_SUPPORTED = 2,
    TP3_TYPE_ERROR = 3,
    TP3_ERROR_PNG_FORMAT_WITHOUT_FILENAME = 4
};

// Arguments
struct Arguments {
    int numRows;                          // Number of rows
    int numCols;                          // Number of columns
    char outputFormat[FORMAT_LENGTH];     // The output format
    char outputFilename[FILENAME_LENGTH]; // The output filename
    enum Error status;                    // The status of the parsing
};

void printUsage(char **argv);

struct Arguments parseArguments(int argc, char **argv);

#endif
