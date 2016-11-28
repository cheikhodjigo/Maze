#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse_args.h"
#include "utils.h"

// Public methods

void printUsage(char **argv) {
    printf(USAGE, argv[0]);
}

// Private method
enum Error castInteger(char *s, int *value) {
    char *p;
    *value = strtol(s, &p, 10);
    return p == NULL || *p == '\0' ? TP3_OK : TP3_TYPE_ERROR;
}

struct Arguments parseArguments(int argc, char **argv) {
    bool showHelp = false, withSolution = false;
    struct Arguments arguments;

    // Default argument
    strcpy(arguments.outputFormat, "text");
    strcpy(arguments.outputFilename, "");
    arguments.status = TP3_OK;
    arguments.numRows = NUM_ROWS_DEFAULT;
    arguments.numCols = NUM_COLS_DEFAULT;

    struct option longOpts[] = {
        // Set flag
        {"help",            no_argument,       (int*)&showHelp, true},
        {"with-solution",   no_argument,       (int*)&withSolution, true},
        // Don't set flag
        {"num-rows",        required_argument, 0, 'r'},
        {"num-cols",        required_argument, 0, 'c'},
        {"output-format",   required_argument, 0, 'f'},
        {"output-filename", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    // Parse options
    while (true) {
        int option_index = 0;
        int c = getopt_long(argc, argv, "rcfo", longOpts, &option_index);
        if (c == -1) break;
        switch (c) {
            case 'r': arguments.status = castInteger(optarg, &arguments.numRows);
                      break;
            case 'c': arguments.status = castInteger(optarg, &arguments.numCols);
                      break;
            case 'f': strncpyLower(arguments.outputFormat, optarg, FORMAT_LENGTH);
                      break;
            case 'o': strncpyLower(arguments.outputFilename, optarg, FILENAME_LENGTH);
                      break;
        }
    }

    if (optind < argc) {
        printf("Error: too many arguments\n");
        printUsage(argv);
        arguments.status = TP3_ERROR_TOO_MANY_ARGUMENTS;
    } else if (showHelp) {
        printUsage(argv);
        exit(0);
    } else if (arguments.status == TP3_TYPE_ERROR) {
        printf("Error: the number of rows and columns must be an integer\n");
        printUsage(argv);
    } else if (strcmp(arguments.outputFormat, "text") != 0
            && strcmp(arguments.outputFormat, "png") != 0) {
        printf("Error: format %s not supported\n", arguments.outputFormat);
        printUsage(argv);
        arguments.status = TP3_ERROR_FORMAT_NOT_SUPPORTED;
    } else if (strcmp(arguments.outputFormat, "png") == 0
            && strcmp(arguments.outputFilename, "") == 0) {
        printf("Error: output filename is mandatory with png format\n");
        printUsage(argv);
        arguments.status = TP3_ERROR_PNG_FORMAT_WITHOUT_FILENAME;
    } else if (strcmp(arguments.outputFormat, "png") == 0
            && withSolution) {
        printf("Error: printing solution with png format is not implemented\n");
        arguments.status = TP3_ERROR_NOT_IMPLEMENTED;
    }
    arguments.withSolution = withSolution;
    return arguments;
}
