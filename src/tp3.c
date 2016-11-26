#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_args.h"
#include "maze.h"
#include "room_partition.h"

void testMaze() {
    //struct Arguments arguments = parseArguments(argc, argv);
    //return arguments.status;
    struct Maze *maze = Maze_randomMaze(8, 10);
    Maze_print(maze);
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

int main(int argc, char **argv) {
    testMaze();
}
