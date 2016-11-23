#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_args.h"
#include "maze.h"

int main(int argc, char **argv) {
    //struct Arguments arguments = parseArguments(argc, argv);
    //return arguments.status;
    struct Maze *maze = Maze_randomMaze(4, 3);
    Maze_print(maze);
    printf("Are rooms consistent? %s\n", Maze_areRoomsConsistent(maze) ? "yes" : "no");
    Maze_free(maze);
}
