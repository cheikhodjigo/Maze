#include <stdio.h>
#include "parse_args.h"
#include <jansson.h>


/*
* Parse the arguments provides by the json file that been 
* choosen by the user
* @params filename      The name of the json file provided
* @params argv          The arguments provided by the user
* @return               The parsed arguments
*
*/
struct Arguments getJson(FILE * filename,char **argv);


/*
* Check if the arguments provided respect all the constraints
* and prints the usage if not. 
* @params arguments     The structure that contains arguments provided by the user
* @params argv          The arguments provided by the user
* @params showHelp      Show if the user want to see the usage or not
*
*/
void checkArg(struct Arguments * arguments,bool showHelp,char **argv);
