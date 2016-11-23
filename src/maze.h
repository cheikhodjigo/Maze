#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

// --------------- //
// Data structures //
// --------------- //

struct Room {   // A room in the maze
    bool right; // Can we go right?
    bool up;    // Can we go up?
    bool left;  // Can we go left?
    bool down;  // Can we go down?
};

struct Maze {
    unsigned int numRows; // The number of rows
    unsigned int numCols; // The number of cols
    struct Room **rooms;  // A matrix of all rooms
};

// ---------------- //
// Public functions //
// ---------------- //

/**
 * Generates a random maze on the square grid.
 *
 * Warning: Don't forget to use ``Maze_free`` when the returned maze is not
 * needed anymore.
 *
 * @param numRows  The number of rows
 * @param numCols  The number of colums
 * @return         The generated maze
 */
struct Maze *Maze_randomMaze(unsigned int numRows, unsigned int numCols);

/**
 * Free the memory used by the given maze.
 *
 * @param maze  The maze to free
 */
void Maze_free(struct Maze *maze);

/**
 * Prints the given maze to stdout.
 *
 * @param maze  The maze to print
 */
void Maze_print(const struct Maze *maze);

/**
 * Returns true if the rooms are consistent.
 *
 * In other words, if it is possible to go from one room to another in a given
 * direction, then it must be possible to move in the opposite direction.
 *
 * @param maze  A pointer to the maze
 * @return      True if and only if the rooms are consistent
 */
bool Maze_areRoomsConsistent(const struct Maze *maze);

#endif
