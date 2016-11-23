#include "maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// ---------------- //
// Public functions //
// ---------------- //

struct Maze *Maze_randomMaze(unsigned int numRows, unsigned int numCols) {
    struct Maze *maze;
    maze = (struct Maze*)malloc(sizeof(struct Maze));
    maze->numRows = numRows;
    maze->numCols = numCols;
    maze->rooms = (struct Room**)malloc(numRows * sizeof(struct Room*));
    for (unsigned int i = 0; i < numRows; ++i) {
        maze->rooms[i] = (struct Room*)malloc(numCols * sizeof(struct Room));
        for (unsigned int j = 0; j < numCols; ++j) {
            maze->rooms[i][j].right = false;
            maze->rooms[i][j].up = false;
            maze->rooms[i][j].left = false;
            maze->rooms[i][j].down = false;
        }
    }
    return maze;
}

void Maze_free(struct Maze *maze) {
    assert(maze != NULL);
    for (unsigned int i = 0; i < maze->numRows; ++i)
        free(maze->rooms[i]);
    free(maze->rooms);
    free(maze);
}

void Maze_print(const struct Maze *maze) {
    assert(maze != NULL);
    for (unsigned int i = 0; i < maze->numRows; ++i) {
        for (unsigned int j = 0; j < maze->numCols; ++j)
            printf("+%c",  maze->rooms[i][j].up ?  ' ' : '-');
        printf("+\n");
        for (unsigned int j = 0; j < maze->numCols; ++j)
            printf("%c ", maze->rooms[i][j].left ? ' ' : '|');
        printf("|\n");
    }
    for (unsigned int j = 0; j < maze->numCols; ++j)
        printf("+-");
    printf("+\n");
}

bool Maze_areRoomsConsistent(const struct Maze *maze) {
    for (unsigned int i = 0; i < maze->numRows; ++i) {
        for (unsigned int j = 0; j < maze->numCols; ++j) {
            if (i < maze->numRows - 1 && maze->rooms[i][j].down !=
                                         maze->rooms[i+1][j].up)
                return false;
            else if (j < maze->numCols - 1 && maze->rooms[i][j].right !=
                                              maze->rooms[i][j+1].left)
                return false;
        }
    }
    return true;
}
