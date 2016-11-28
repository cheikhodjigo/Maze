#include "maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "array.h"
#include "utils.h"

// ----------------- //
// Private functions //
// ----------------- //

struct RoomsTransition {
    unsigned int i;
    unsigned int j;
    bool horizontal; // Horizontal or vertical?
};

void Maze_makeTransitions(struct RoomsTransition transitions[],
                          unsigned int numRows,
                          unsigned int numCols) {
    unsigned int i, j, k = 0;
    for (i = 0; i < numRows; ++i) {
        for (j = 0; j < numCols; ++j) {
            if (j < numCols - 1) {
                transitions[k].i = i;
                transitions[k].j = j;
                transitions[k].horizontal = true;
                ++k;
            }
            if (i < numRows - 1) {
                transitions[k].i = i;
                transitions[k].j = j;
                transitions[k].horizontal = false;
                ++k;
            }
        }
    }
}

void Maze_shuffleTransitions(struct RoomsTransition transitions[],
                             unsigned int numTransitions) {
    srand(time(NULL));
    unsigned int k;
    for (k = 0; k < numTransitions; ++k) {
        int i = rand() % numTransitions;
        int j = rand() % numTransitions;
        struct RoomsTransition temp = transitions[i];
        transitions[i] = transitions[j];
        transitions[j] = temp;
    }
}

void Maze_mergeRooms(struct Maze *maze,
                     struct RoomsTransition transitions[],
                     unsigned int numTransitions) {
    unsigned int k;
    for (k = 0; k < numTransitions; ++k) {
        unsigned int i1 = transitions[k].i;
        unsigned int j1 = transitions[k].j;
        bool horizontal = transitions[k].horizontal;
        unsigned int i2 = horizontal ? i1 : i1 + 1;
        unsigned int j2 = horizontal ? j1 + 1 : j1;
        if (!RoomPartition_areInSameClass(&maze->partition, i1, j1, i2, j2)) {
            RoomPartition_merge(&maze->partition, i1, j1, i2, j2);
            if (horizontal) {
                maze->rooms[i1][j1].right = true;
                maze->rooms[i2][j2].left = true;
            } else {
                maze->rooms[i1][j1].down = true;
                maze->rooms[i2][j2].up = true;
            }
        }
    }
}

void Maze_makePerfect(struct Maze *maze) {
    struct RoomsTransition *transitions;
    int numTransitions = maze->numRows * (maze->numCols - 1) +
                         (maze->numRows - 1) * maze->numCols;
    transitions = (struct RoomsTransition*)malloc(numTransitions * sizeof(struct RoomsTransition));
    Maze_makeTransitions(transitions, maze->numRows, maze->numCols);
    Maze_shuffleTransitions(transitions, numTransitions);
    Maze_mergeRooms(maze, transitions, numTransitions);
    free(transitions);
};

void Maze_toString(const struct Maze *maze,
                   char** s) {
    unsigned int i, j;
    for (i = 0; i < maze->numRows; ++i) {
        for (j = 0; j < maze->numCols; ++j) {
            s[2*i + 1][2*j + 1] = ' ';
            s[2*i][2*j] = '+';
            s[2*i + 2][2*j] = '+';
            s[2*i][2*j + 2] = '+';
            s[2*i + 2][2*j + 2] = '+';
            s[2*i][2*j + 1] = maze->rooms[i][j].up ?  ' ' : '-';
            s[2*i + 1][2*j] = maze->rooms[i][j].left ?  ' ' : '|';
            s[2*i + 1][2*j + 2] = maze->rooms[i][j].right ?  ' ' : '|';
            s[2*i + 2][2*j + 1] = maze->rooms[i][j].down ?  ' ' : '-';
        }
    }
}

void Maze_addSolution(const struct Maze *maze,
                      char** s) {
    unsigned int i, j, ip, jp, k;
    ip = Array_get(maze->path, 0)->first;
    jp = Array_get(maze->path, 0)->second;
    for (k = 0; k < maze->path->length; ++k) {
        i = Array_get(maze->path, k)->first;
        j = Array_get(maze->path, k)->second;
        s[2*i + 1][2*j + 1] = 'X';
        s[i + ip + 1][j + jp + 1] = 'X';
        ip = i;
        jp = j;
    }
}

// ---------------- //
// Public functions //
// ---------------- //

struct Maze *Maze_randomMaze(unsigned int numRows, unsigned int numCols) {
    struct Maze *maze;
    maze = (struct Maze*)malloc(sizeof(struct Maze));
    maze->numRows = numRows;
    maze->numCols = numCols;
    maze->rooms = (struct Room**)malloc(numRows * sizeof(struct Room*));
    unsigned int i, j;
    for (i = 0; i < numRows; ++i) {
        maze->rooms[i] = (struct Room*)malloc(numCols * sizeof(struct Room));
        for (j = 0; j < numCols; ++j) {
            maze->rooms[i][j].right = false;
            maze->rooms[i][j].up = false;
            maze->rooms[i][j].left = false;
            maze->rooms[i][j].down = false;
        }
    }
    maze->partition = RoomPartition_create(numRows, numCols);
    Maze_makePerfect(maze);
    maze->path = Maze_path(maze, 0, 0, numRows - 1, numCols - 1);
    return maze;
}

void Maze_free(struct Maze *maze) {
    assert(maze != NULL);
    RoomPartition_free(&maze->partition);
    unsigned int i;
    for (i = 0; i < maze->numRows; ++i)
        free(maze->rooms[i]);
    free(maze->rooms);
    free(maze);
    Array_delete(maze->path);
}

void Maze_print(const struct Maze *maze, bool withSolution) {
    assert(maze != NULL);
    unsigned int i, j;
    unsigned int height = 2 * maze->numRows + 1;
    unsigned int width = 2 * maze->numCols + 1;
    char **s = (char**)malloc(height * sizeof(char*));
    for (i = 0; i < height; ++i) {
        s[i] = (char*)malloc(width * sizeof(char));
    }
    Maze_toString(maze, s);
    if (withSolution) Maze_addSolution(maze, s);
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j)
            printf("%c",  s[i][j]);
        printf("\n");
    }
    for (i = 0; i < maze->numRows; ++i) {
        free(s[i]);
    }
    free(s);
}

bool Maze_areRoomsConsistent(const struct Maze *maze) {
    unsigned int i, j;
    for (i = 0; i < maze->numRows; ++i) {
        for (j = 0; j < maze->numCols; ++j) {
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

// ---- //
// Path //
// ---- //

void Maze_visit(const struct Maze *maze,
                int currenti,
                int currentj,
                int previousi,
                int previousj,
                bool **visited,
                struct uiPair **parent) {
    if (!visited[currenti][currentj]) {
        visited[currenti][currentj] = true;
        parent[currenti][currentj].first = previousi;
        parent[currenti][currentj].second = previousj;

        // Going right
        if (maze->rooms[currenti][currentj].right) {
            Maze_visit(maze, currenti, currentj + 1, currenti, currentj, visited, parent);
        }
        // Going left
        if (maze->rooms[currenti][currentj].left) {
            Maze_visit(maze, currenti, currentj - 1, currenti, currentj, visited, parent);
        }
        // Going up
        if (maze->rooms[currenti][currentj].up) {
            Maze_visit(maze, currenti - 1, currentj, currenti, currentj, visited, parent);
        }
        // Going down
        if (maze->rooms[currenti][currentj].down) {
            Maze_visit(maze, currenti + 1, currentj, currenti, currentj, visited, parent);
        }
    }
}

struct Array *Maze_path(const struct Maze *maze,
                        unsigned int room1i,
                        unsigned int room1j,
                        unsigned int room2i,
                        unsigned int room2j) {
    bool **visited = (bool**)malloc(maze->numRows * sizeof(bool*));
    struct uiPair **parent = (struct uiPair**)malloc(maze->numRows * sizeof(struct uiPair*));
    unsigned int i, j;
    for (i = 0; i < maze->numRows; ++i) {
        visited[i] = (bool*)malloc(maze->numCols * sizeof(bool));
        parent[i] = (struct uiPair*)malloc(maze->numCols * sizeof(struct uiPair));
        for (j = 0; j < maze->numCols; ++j) {
            visited[i][j] = false;
        }
    }

    Maze_visit(maze, room2i, room2j, room2i, room2j, visited, parent);

    struct Array *path = Array_create();
    struct uiPair pair;
    i = room1i; j = room1j;
    do {
        pair.first = i;
        pair.second = j;
        Array_append(path, &pair);
        unsigned int ip = parent[i][j].first;
        unsigned int jp = parent[i][j].second;
        i = ip;
        j = jp;
    } while (i != room2i || j != room2j);
    pair.first = room2i;
    pair.second = room2j;
    Array_append(path, &pair);

    for (i = 0; i < maze->numRows; ++i) {
        free(visited[i]);
        free(parent[i]);
    }
    free(parent);
    return path;
}
