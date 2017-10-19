/**
 * File parse_args.c
 *
 * Implements parse_args.h, using the getopt library to simplify the
 * processing.
 *
 * @author Alexandre Blondin Masse
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "parse_args.h"
#include "utils.h"
#include "color.h"

// -------------- //
// Private method //
// -------------- //

enum Error castUnsignedInteger(const char *s,
                               unsigned int *value) {
    char *p;
    int signedValue;
    signedValue = strtol(s, &p, 10);
    if (p != NULL && *p != '\0') {
        return TP2_TYPE_ERROR;
    } else if (signedValue < 0) {
        return TP2_VALUE_ERROR;
    } else {
        *value = (unsigned int)signedValue;
        return TP2_OK;
    }
}

/**
 * Retrieves the (row, column) coordinates from a string.
 *
 * @param s       The string containing the coordinates
 * @param row     The parsed row
 * @param column  The parsed column
 * @return        The status of the operation
 */
enum Error castCoordinates(const char *s,
                           unsigned int *row,
                           unsigned int *col) {
    char tail = '\0';
    int signedRow, signedCol;
    int numParsed = sscanf(s, "%d,%d%c", &signedRow, &signedCol, &tail);
    if (numParsed == 2 && tail == '\0' && signedRow >= 0 && signedCol >= 0) {
        *row = (unsigned int)signedRow;
        *col = (unsigned int)signedCol;
        return TP2_OK;
    } else {
        return TP2_ERROR_COORDINATES_FORMAT;
    }
}

// -------------- //
// Public methods //
// -------------- //

void printUsage(char **argv) {
    printf(USAGE, argv[0]);
}

struct Arguments parseArguments(int argc, char **argv) {
    bool showHelp = false;
    bool endRoomProvided = false;
    struct Arguments arguments;

    // Default argument
    strcpy(arguments.outputFormat, TEXT_FORMAT);
    strcpy(arguments.outputFilename, "");
    strcpy(arguments.wallsColor, COLOR_DEFAULT);
    arguments.status = TP2_OK;
    arguments.numRows = NUM_ROWS_DEFAULT;
    arguments.numCols = NUM_COLS_DEFAULT;
    arguments.startRoomi = 0;
    arguments.startRoomj = 0;
    arguments.withSolution = false;

    struct option longOpts[] = {
        // Set flag
        {"help",            no_argument,       0, 'h'},
        {"with-solution",   no_argument,       0, 's'},
        // Don't set flag
        {"num-rows",        required_argument, 0, 'r'},
        {"num-cols",        required_argument, 0, 'c'},
        {"start",           required_argument, 0, 't'},
        {"end",             required_argument, 0, 'e'},
        {"walls-color",     required_argument, 0, 'w'},
        {"output-format",   required_argument, 0, 'f'},
        {"output-filename", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    // Parse options
    while (true) {
        int option_index = 0;
        int c = getopt_long(argc, argv, "hsr:c:t:e:w:f:o:", longOpts, &option_index);
        if (c == -1) break;
        switch (c) {
            case 'h': showHelp = true;
                      break;
            case 's': arguments.withSolution = true;
                      break;
            case 'r': if (arguments.status == TP2_OK)
                          arguments.status = castUnsignedInteger(optarg, &arguments.numRows);
                      break;
            case 'c': if (arguments.status == TP2_OK)
                          arguments.status = castUnsignedInteger(optarg, &arguments.numCols);
                      break;
            case 't': if (arguments.status == TP2_OK)
                          arguments.status = castCoordinates(optarg,
                                                             &arguments.startRoomi,
                                                             &arguments.startRoomj);
                      break;
            case 'e': if (arguments.status == TP2_OK)
                          arguments.status = castCoordinates(optarg,
                                                             &arguments.endRoomi,
                                                             &arguments.endRoomj);
                      endRoomProvided = true;
                      break;
            case 'w': strncpyLower(arguments.wallsColor, optarg, COLOR_LENGTH);
                      break;
            case 'f': strncpyLower(arguments.outputFormat, optarg, FORMAT_LENGTH);
                      break;
            case 'o': strncpyLower(arguments.outputFilename, optarg, FILENAME_LENGTH);
                      break;
            case '?': if (arguments.status == TP2_OK)
                          arguments.status = TP2_ERROR_BAD_OPTION;
                      break;
        }
    }

    if (!endRoomProvided) {
        arguments.endRoomi = arguments.numRows - 1;
        arguments.endRoomj = arguments.numCols - 1;
    }
    if (optind < argc) {
        printf("Error: too many arguments\n");
        printUsage(argv);
        arguments.status = TP2_ERROR_TOO_MANY_ARGUMENTS;
    } else if (showHelp) {
        printUsage(argv);
        exit(TP2_OK);
    } else if (arguments.status == TP2_TYPE_ERROR) {
        printf("Error: the number of rows and columns must be integers\n");
        printUsage(argv);
    } else if (arguments.status == TP2_VALUE_ERROR ||
               arguments.numRows == 0 ||
               arguments.numCols == 0) {
        printf("Error: the number of rows and column must be a positive integer\n");
        arguments.status = TP2_VALUE_ERROR;
        printUsage(argv);
    } else if (arguments.status == TP2_ERROR_COORDINATES_FORMAT) {
        printf("Error: the start and end rooms coordinates are invalid\n"),
        printUsage(argv);
    } else if (arguments.startRoomi >= arguments.numRows ||
               arguments.startRoomj >= arguments.numCols) {
        printf("Error: the start room coordinates %d,%d are out of bound\n",
               arguments.startRoomi, arguments.startRoomj),
        arguments.status = TP2_ERROR_COORDINATES_OUT_OF_BOUND;
        printUsage(argv);
    } else if (arguments.endRoomi >= arguments.numRows ||
               arguments.endRoomj >= arguments.numCols) {
        printf("Error: the end room coordinates %d,%d are out of bound\n",
               arguments.startRoomi, arguments.startRoomj),
        arguments.status = TP2_ERROR_COORDINATES_OUT_OF_BOUND;
        printUsage(argv);
    } else if (strcmp(arguments.outputFormat, TEXT_FORMAT) != 0
            && strcmp(arguments.outputFormat, PNG_FORMAT) != 0) {
        printf("Error: format %s not supported\n", arguments.outputFormat);
        printUsage(argv);
        arguments.status = TP2_ERROR_FORMAT_NOT_SUPPORTED;
    } else if (strcmp(arguments.outputFormat, PNG_FORMAT) == 0
            && strcmp(arguments.outputFilename, "") == 0) {
        printf("Error: output filename is mandatory with png format\n");
        printUsage(argv);
        arguments.status = TP2_ERROR_PNG_FORMAT_WITHOUT_FILENAME;
    } else if (!Color_isNamedColor(arguments.wallsColor)) {
        printf("Error: the color \"%s\" is not recognized\n", arguments.wallsColor);
        arguments.status = TP2_ERROR_INVALID_COLOR;
    }
    return arguments;
}
