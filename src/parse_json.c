#include <stdio.h>
#include "parse_json.h"
#include <jansson.h>
#include <string.h>

struct Arguments getJson(FILE * filename){
    struct Arguments arguments;
    bool endRoomProvided = false;
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
        arguments.status = TP2_ERROR_FORMAT_NOT_SUPPORTED;
        return arguments;
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
        if(strcmp(key,"num-rows") == 0){
            if(!json_is_integer(value)){
                fprintf(stderr," Error: the number of rows and columns must be an integer\n");
                arguments.status = TP2_VALUE_ERROR;
                return arguments;
            }
            arguments.numRows = (unsigned int)json_integer_value(value);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"num-cols") == 0){
            if(!json_is_integer(value)){
                fprintf(stderr," Error: the number of rows and columns must be an integer\n");
                arguments.status = TP2_VALUE_ERROR;
                return arguments;
            }
            arguments.numCols =(unsigned int)json_integer_value(value);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"start") == 0){
            if(!json_is_array(value)){
                fprintf(stderr," Error: the start and end rooms must be an array\n");
                arguments.status = TP2_VALUE_ERROR;
                return arguments;
            }
            if(json_array_size(value) > 2){
                fprintf(stderr," Error: the start and end rooms must be an array of size 2\n");
                arguments.status = TP2_VALUE_ERROR;
                return  arguments;
            }
            size_t a;
            for(a = 0; a < json_array_size(value);a++){
                arrayOfInt= json_array_get(value,a);
                if(!json_is_integer(arrayOfInt)){
                    fprintf(stderr," Error: the start and end rooms must be an array of size 2\n");
                    arguments.status = TP2_VALUE_ERROR;
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
                return arguments;
            }
            if(json_array_size(value) > 2){
                fprintf(stderr," Error: the start and end rooms must be an array of size 2\n");
                arguments.status = TP2_VALUE_ERROR;
                return  arguments;
            }
            size_t a;
            for(a = 0; a < json_array_size(value);a++){
                arrayOfInt= json_array_get(value,a);
                if(!json_is_integer(arrayOfInt)){
                    fprintf(stderr," Error: the start and end rooms must be an array of size 2\n");
                    arguments.status = TP2_VALUE_ERROR;
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
                arguments.status = TP2_VALUE_ERROR;
                return arguments;
            }
            arguments.withSolution = json_boolean_value(value);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"walls-color") == 0){
            if(!json_is_string(value)){
                fprintf(stderr," Error: params walls-color must be a string\n");
                arguments.status = TP2_VALUE_ERROR;
                return arguments;
            }
            text = json_string_value(value);
            strncpy(arguments.wallsColor, text, COLOR_LENGTH);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"output-format") == 0){
            if(!json_is_string(value)){
                fprintf(stderr," Error: params output-format must be a string\n");
                arguments.status = TP2_VALUE_ERROR;
                return arguments;
            }
            text = json_string_value(value);
            strncpy(arguments.outputFormat, text, FORMAT_LENGTH);
            arguments.status = TP2_OK;
        }else if(strcmp(key,"output-filename") == 0){
            if(!json_is_string(value)){
                fprintf(stderr," Error: params output-filename must be a string\n");
                arguments.status = TP2_VALUE_ERROR;
                return arguments;
            }
            text = json_string_value(value);
            strncpy(arguments.outputFilename, text, FILENAME_LENGTH);
            arguments.status = TP2_OK;
        }else{
            fprintf(stderr," Error: params %s does not exists\n",json_string_value(value));
            arguments.status = TP2_TYPE_ERROR;
            return arguments;
        }
    }
    if (!endRoomProvided) {
        arguments.endRoomi = arguments.numRows - 1;
        arguments.endRoomj = arguments.numCols - 1;
    }
    json_decref(root);
    return arguments;
}
