/**
 * File maze.h
 *
 * Provides a data structure for representing mazes and services for handling
 * them.
 *
 * Each maze is divided into rooms, i.e. individual unit square cells that can
 * have walls in the four basic directions (right, up, left, down). The
 * following services are available:
 *
 * - Generating a random maze with given numbers of rows and columns
 *   (`Maze_randomMaze``);
 * - Freeing a maze (``Maze_free``);
 * - Priting an ASCII representation of a maze (``Maze_print``);
 * - Checking if the rooms are consistent, i.e. for each wall between a pair of
 *   adjacent rooms, both rooms have the corresponding wall
 *   (``Maze_areRoomsConsistent``), mostly used for debugging;
 * - Computing the unique path in the maze from the room `(0,0)` to the room
 *   `(r-1,c-1)` (``Maze_path``).
 *
 * @author Alexandre Blondin Masse
 */
#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include "room_partition.h"
#include "array.h"
#include "parse_args.h"

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
 * @param arguments  The parameters of the maze
 * @return           The generated maze
 */
struct Maze *Maze_randomMaze(const struct Arguments *arguments);

/**
 * Free the memory used by the given maze.
 *
 * @param maze  The maze to free
 */
void Maze_free(struct Maze *maze);

/**
 * Prints the given maze to stdout.
 *
 * @param maze          The maze to print
 * @param withSolution  If true, then the solution is printed
 */
void Maze_print(const struct Maze *maze, bool withSolution);

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
/**
* Print the maze in the dot format 
* 
* @param maze   The maze
*      
*/
void Maze_dot(const struct Maze * maze);
#endif
