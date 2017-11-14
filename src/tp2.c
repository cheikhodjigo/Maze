#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_args.h"
#include "maze.h"
#include "drawing.h"

int main(int argc, char **argv) {
    struct Arguments arguments = parseArguments(argc, argv);
    if (arguments.status != TP2_OK) {
        return arguments.status;
    } else {
        struct Maze *maze = Maze_randomMaze(&arguments);
        if (strcmp(arguments.outputFormat, TEXT_FORMAT) == 0) {
            Maze_print(maze, arguments.withSolution);
        } else if (strcmp(arguments.outputFormat, PNG_FORMAT) == 0) {
            Drawing_drawMaze(maze, &arguments);
        } else if (strcmp(arguments.outputFormat, DOT_FORMAT) == 0){
            Maze_dot(maze);
        }
    }
    return TP2_OK;
}
