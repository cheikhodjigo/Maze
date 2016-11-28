#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include "room_partition.h"
#include "array.h"

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
    unsigned int numRows;           // The number of rows
    unsigned int numCols;           // The number of cols
    struct Room **rooms;            // A matrix of all rooms
    struct RoomPartition partition; // A partition of the rooms
    struct Array *path;             // The solution of the maze
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

/**
 * Returns the unique path between the two given rooms.
 *
 * Since the maze is perfect by construction, there always exists such a path
 * and it is unique. The path is returned as an ordered array of the successive
 * rooms encountered.
 * 
 * @param maze    The maze
 * @param room1i  The row number of the start room
 * @param room1j  The column number of the start room
 * @param room2i  The row number of the end room
 * @param room2j  The column number of the end room
 * @return        The resulting path
 */
struct Array *Maze_path(const struct Maze *maze,
                        unsigned int room1i,
                        unsigned int room1j,
                        unsigned int room2i,
                        unsigned int room2j);

#endif
