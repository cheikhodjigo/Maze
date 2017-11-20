#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_args.h"
#include "parse_json.h"
#include <unistd.h>
#include "maze.h"
#include "drawing.h"

int main(int argc, char **argv) {
    struct Arguments arguments;// = parseArguments(argc, argv);
    if(!isatty(STDIN_FILENO) && argc == 1){
        arguments = getJson(stdin,argv);
    }else {
        arguments = parseArguments(argc, argv);
    } 
    
    if (arguments.status != TP2_OK) {
        return arguments.status;
    } else {
        struct Maze *maze = Maze_randomMaze(&arguments);
        if (strcmp(arguments.outputFormat, TEXT_FORMAT) == 0) {
            Maze_print(maze, arguments.withSolution);
        } else if (strcmp(arguments.outputFormat, PNG_FORMAT) == 0) {
            Drawing_drawMaze(maze, &arguments);
        } else if (strcmp(arguments.outputFormat, DOT_FORMAT) == 0){
            Maze_dot(maze,arguments.withSolution);
        }
    }
    return TP2_OK;
}
