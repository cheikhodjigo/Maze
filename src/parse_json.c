#include <stdio.h>
#include "parse_json.h"
#include <jansson.h>
#include <string.h>
#include "utils.h"
#include "color.h"

struct Arguments getJson(FILE * filename,char ** argv){
    struct Arguments arguments;
    bool endRoomProvided = false;
    bool showHelp = false;
    const char * text;
    json_t *root;
    json_t *arrayOfInt;
    json_error_t error;
    
    //Defauls params
    strcpy(arguments.outputFormat, TEXT_FORMAT);
    strcpy(arguments.outputFilename, "");
    strcpy(arguments.wallsColor, COLOR_DEFAULT);
    arguments.status = TP2_OK;
    arguments.numRows = NUM_ROWS_DEFAULT;
    arguments.numCols = NUM_COLS_DEFAULT;
    arguments.startRoomi = 0;
    arguments.startRoomj = 0;
    arguments.withSolution = false;
    
    root = json_loadf(filename,0,&error);
    if(!root){
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        arguments.status = TP2_JSON_FORMAT_INVALID;
        printUsage(argv);
        return arguments;
    }
    if(!json_is_object(root))
    {
        fprintf(stderr, "error: root is not an array\n");
        json_decref(root);
        arguments.status = TP2_JSON_FORMAT_INVALID;
        printUsage(argv);
        return arguments;
    }
    
    const char *key;
    json_t *value;
    
    json_object_foreach(root, key, value) {
        if(strcmp(key,"num-rows") == 0){
            if(!json_is_integer(value)){
                fprintf(stderr," Error: the number of rows and columns must be an integer\n");
                arguments.status = TP2_JSON_VALUE_INVALID;
                printUsage(argv);
                return arguments;
            }
            arguments.numRows = (unsigned int)json_integer_value(value);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"num-cols") == 0){
            if(!json_is_integer(value)){
                fprintf(stderr," Error: the number of rows and columns must be an integer\n");
                arguments.status = TP2_JSON_VALUE_INVALID;
                printUsage(argv);
                return arguments;
            }
            arguments.numCols =(unsigned int)json_integer_value(value);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"start") == 0){
            if(!json_is_array(value)){
                fprintf(stderr," Error: the start and end rooms must be an array\n");
                arguments.status = TP2_JSON_VALUE_INVALID;
                printUsage(argv);
                return arguments;
            }
            if(json_array_size(value) > 2){
                fprintf(stderr," Error: the start and end rooms must be an array of size 2\n");
                arguments.status = TP2_JSON_VALUE_INVALID;
                printUsage(argv);
                return  arguments;
            }
            size_t a;
            for(a = 0; a < json_array_size(value);a++){
                arrayOfInt= json_array_get(value,a);
                if(!json_is_integer(arrayOfInt)){
                    fprintf(stderr," Error: the start and end rooms must be an array of size 2\n");
                    arguments.status = TP2_JSON_ARRAYVALUE_INVALID;
                    printUsage(argv);
                    return  arguments;
                }
                if(a == 0) arguments.startRoomi = (unsigned int)json_integer_value(arrayOfInt);
                if(a == 1) arguments.startRoomj = (unsigned int)json_integer_value(arrayOfInt);
            }
            arguments.status = TP2_OK;
            
        }else if(strcmp(key,"end") == 0){
            if(!json_is_array(value)){
                fprintf(stderr," Error: the start and end rooms must be an array\n");
                arguments.status = TP2_VALUE_ERROR;
                printUsage(argv);
                return arguments;
            }
            if(json_array_size(value) > 2){
                fprintf(stderr," Error: the start and end rooms must be an array of size 2\n");
                arguments.status = TP2_JSON_ARRAYVALUE_INVALID;
                printUsage(argv);
                return  arguments;
            }
            size_t a;
            for(a = 0; a < json_array_size(value);a++){
                arrayOfInt= json_array_get(value,a);
                if(!json_is_integer(arrayOfInt)){
                    fprintf(stderr," Error: the start and end rooms must be an array of size 2\n");
                    arguments.status = TP2_VALUE_ERROR;
                    printUsage(argv);
                    return  arguments;
                }
                if(a == 0) arguments.endRoomi = (unsigned int)json_integer_value(arrayOfInt);
                if(a == 1) arguments.endRoomj = (unsigned int)json_integer_value(arrayOfInt);
            }
            endRoomProvided = true;
            arguments.status = TP2_OK;
        }else if(strcmp(key,"with-solution") == 0){
            if(!json_is_boolean(value)){
                fprintf(stderr," Error: params with-solution must be a boolean\n");
                arguments.status = TP2_JSON_VALUE_INVALID;
                printUsage(argv);
                return arguments;
            }
            arguments.withSolution = json_boolean_value(value);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"walls-color") == 0){
            if(!json_is_string(value)){
                fprintf(stderr," Error: params walls-color must be a string\n");
                arguments.status = TP2_JSON_VALUE_INVALID;
                printUsage(argv);
                return arguments;
            }
            text = json_string_value(value);
            strncpy(arguments.wallsColor, text, COLOR_LENGTH);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"output-format") == 0){
            if(!json_is_string(value)){
                fprintf(stderr," Error: params output-format must be a string\n");
                arguments.status = TP2_JSON_VALUE_INVALID;
                printUsage(argv);
                return arguments;
            }
            text = json_string_value(value);
            strncpy(arguments.outputFormat, text, FORMAT_LENGTH);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"output-filename") == 0){
            if(!json_is_string(value)){
                fprintf(stderr," Error: params output-filename must be a string\n");
                arguments.status = TP2_JSON_VALUE_INVALID;
                printUsage(argv);
                return arguments;
            }
            text = json_string_value(value);
            strncpy(arguments.outputFilename, text, FILENAME_LENGTH);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"help") == 0){
            showHelp = true;            
        }else{
            fprintf(stderr," Error: params %s does not exists\n",key);
            arguments.status = TP2_JSON_KEY_INVALID;
            printUsage(argv);    
            return arguments;
        }
    }
    if (!endRoomProvided) {
        arguments.endRoomi = arguments.numRows - 1;
        arguments.endRoomj = arguments.numCols - 1;
    }
    checkArg(&arguments,showHelp,argv);
    json_decref(root);
    return arguments;
}

void checkArg(struct Arguments * arguments,bool showHelp,char **argv){
    if (showHelp) {
        printUsage(argv);
        exit(TP2_OK);
    } else if (arguments->status == TP2_TYPE_ERROR) {
        printf("Error: the number of rows and columns must be integers\n");
        printUsage(argv);
    } else if (arguments->status == TP2_VALUE_ERROR ||
               arguments->numRows == 0 ||
               arguments->numCols == 0) {
        printf("Error: the number of rows and column must be a positive integer\n");
        arguments->status = TP2_VALUE_ERROR;
        printUsage(argv);
    } else if (arguments->status == TP2_ERROR_COORDINATES_FORMAT) {
        printf("Error: the start and end rooms coordinates are invalid\n"),
        printUsage(argv);
    } else if (arguments->startRoomi >= arguments->numRows ||
               arguments->startRoomj >= arguments->numCols) {
        printf("Error: the start room coordinates %d,%d are out of bound\n",
               arguments->startRoomi, arguments->startRoomj),
        arguments->status = TP2_ERROR_COORDINATES_OUT_OF_BOUND;
        printUsage(argv);
    } else if (arguments->endRoomi >= arguments->numRows ||
               arguments->endRoomj >= arguments->numCols) {
        printf("Error: the end room coordinates %d,%d are out of bound\n",
               arguments->endRoomi, arguments->endRoomj),
        arguments->status = TP2_ERROR_COORDINATES_OUT_OF_BOUND;
        printUsage(argv);
    } else if (strcmp(arguments->outputFormat, TEXT_FORMAT) != 0
            && strcmp(arguments->outputFormat, PNG_FORMAT) != 0
            && strcmp(arguments->outputFormat, DOT_FORMAT) != 0) {
        printf("Error: format %s not supported\n", arguments->outputFormat);
        printUsage(argv);
        arguments->status = TP2_ERROR_FORMAT_NOT_SUPPORTED;
    } else if (strcmp(arguments->outputFormat, PNG_FORMAT) == 0
            && strcmp(arguments->outputFilename, "") == 0) {
        printf("Error: output filename is mandatory with png format\n");
        printUsage(argv);
        arguments->status = TP2_ERROR_PNG_FORMAT_WITHOUT_FILENAME;
    } else if (!Color_isNamedColor(arguments->wallsColor)) {
        printf("Error: the color \"%s\" is not recognized\n", arguments->wallsColor);
        arguments->status = TP2_ERROR_INVALID_COLOR;
    }

}
