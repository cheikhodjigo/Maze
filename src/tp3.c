#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_args.h"
#include "array.h"
#include "maze.h"
#include "room_partition.h"
#include "drawing.h"

void testMaze() {
    struct Maze *maze = Maze_randomMaze(8, 10);
    Maze_print(maze, false);
    printf("Are rooms consistent? %s\n", Maze_areRoomsConsistent(maze) ? "yes" : "no");
    Maze_free(maze);
}

void testPartition() {
    struct RoomPartition partition = RoomPartition_create(4, 3);
    RoomPartition_print(&partition);
    RoomPartition_merge(&partition, 0, 0, 0, 1);
    RoomPartition_print(&partition);
    RoomPartition_merge(&partition, 0, 0, 0, 2);
    RoomPartition_print(&partition);
    RoomPartition_merge(&partition, 0, 0, 0, 1);
    RoomPartition_print(&partition);
}

void testArray() {
    struct Array *array = Array_create();
    struct uiPair pair;
    pair.first = 2; pair.second = 3;
    Array_append(array, &pair);
    pair.first = 5; pair.second = 7;
    Array_append(array, &pair);
    Array_print(array);
    Array_delete(array);
}

int main(int argc, char **argv) {
    struct Arguments arguments = parseArguments(argc, argv);
    if (arguments.status != TP3_OK) {
        //TODO: Error message?
        return arguments.status;
    } else {
        struct Maze *maze = Maze_randomMaze(arguments.numRows,
                                            arguments.numCols);
        if (strcmp(arguments.outputFormat, "text") == 0) {
            Maze_print(maze, arguments.withSolution);
        } else if (strcmp(arguments.outputFormat, "png") == 0) {
    	    Drawing_drawMaze(maze, arguments.outputFilename);
        }
    }
    return TP3_OK;
}
