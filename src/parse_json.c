#include <stdio.h>
#include "parse_json.h"
#include <jansson.h>
#include <string.h>


struct Arguments getJson(FILE * filename){
    struct Arguments arguments;
    json_t *root;
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
     //   return TP2_ERROR_BAD_OPTION;
    }
    if(!json_is_object(root))
    {
        fprintf(stderr, "error: root is not an array\n");
        json_decref(root);
        arguments.status = TP2_TYPE_ERROR;
        return arguments;
    }

    const char *key;
    json_t *value;

    json_object_foreach(root, key, value) {
    /* block of code that uses key and value */
        if(strcmp(key,"num-rows") == 0){
            if(!json_is_integer(value)){
                fprintf(stderr," Error: the number of rows and columns must be an integer\n");
                arguments.status = TP2_VALUE_ERROR;
                return arguments;
            }
        }
    }
    return arguments;
}
