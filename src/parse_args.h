/**
 * File parse_args.h
 *
 * Provides basic services to process the main arguments. Error codes are also
 * provided in the case of invalid input from the user.
 *
 * @author Alexandre Blondin Masse
 */
#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include <stdbool.h>

#define TEXT_FORMAT "text"
#define PNG_FORMAT "png"
#define COLOR_DEFAULT "black"
#define FORMAT_LENGTH 5
#define FILENAME_LENGTH 20
#define COLOR_LENGTH 15
#define NUM_ROWS_DEFAULT 5
#define NUM_COLS_DEFAULT 5
#define USAGE "\
Usage: %s [--help] [--with-solution] [--num-rows VALUE] [--num-cols VALUE]\n\
    [--walls-color VALUE] [--output-format STRING] [--output-filename FILENAME]\n\
\n\
Generates a random maze on the square grid.\n\
\n\
Optional arguments:\n\
  --help                   Shows this help message and exit\n\
  --num-rows VALUE         The number of rows in the maze.\n\
                           The default value is 5.\n\
  --num-cols VALUE         The number of columns in the maze.\n\
                           The default value is 5.\n\
  --with-solution          Also displays solution in the maze.\n\
  --walls-color VALUE      The color of the walls in the maze (e.g. \"navy\").\n\
                           The name must be one of the 16 basic HTML colors.\n\
                           Defaults to \"black\". The option is ignored if the\n\
                           ouput format is \"text\".\n\
  --output-format STRING   Selects the ouput format (either \"text\" or \"png\").\n\
                           The default format is \"text\".\n\
  --output-filename STRING The name of the output file.\n\
                           Mandatory for png format.\n\
                           If not specified, displays on stdout.\n\
"

// Parsing errors
enum Error {
    TP2_OK = 0,
    TP2_ERROR_TOO_MANY_ARGUMENTS = 1,
    TP2_ERROR_FORMAT_NOT_SUPPORTED = 2,
    TP2_TYPE_ERROR = 3,
    TP2_ERROR_PNG_FORMAT_WITHOUT_FILENAME = 4,
    TP2_ERROR_BAD_OPTION = 5,
    TP2_ERROR_NOT_IMPLEMENTED = 6,
    TP2_ERROR_INVALID_COLOR = 7,
};

// Arguments
struct Arguments {                        // User arguments
    int numRows;                          // Number of rows
    int numCols;                          // Number of columns
    bool withSolution;                    // Displays solution?
    char outputFormat[FORMAT_LENGTH];     // The output format
    char outputFilename[FILENAME_LENGTH]; // The output filename
    char wallsColor[COLOR_LENGTH];        // The color of the walls
    enum Error status;                    // The status of the parsing
};

/**
 * Prints how to use the program.
 *
 * @param argv  The arguments provided by the user
 */
void printUsage(char **argv);

/**
 * Parses the arguments provided by the user.
 *
 * @param argc  The number of arguments including the program name
 * @param argv  The arguments provided by the user
 * @return      The parsed arguments
 */
struct Arguments parseArguments(int argc, char **argv);

#endif
