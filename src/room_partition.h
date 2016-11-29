/**
 * File room_partition.h
 *
 * Implements the disjoint-set data structure for representing connected rooms.
 * The usual services are available:
 *
 * - Creating a trivial disjoint-set, where each room is in its own component
 *   (`RoomPartition_create``);
 * - Merging two components of given rooms (``RoomPartition_merge``). In other
 *   words, if there is no wall between two rooms, then they are connected and
 *   all rooms connected to them are also connected.
 * - Checking if two rooms are connected (``RoomPartition_areInSameClass``);
 * - Counting the number of classes, i.e. the number of groups of rooms that
 *   are not connected (``RoomPartition_numberOfClasses``);
 * - Checking if all rooms are connected (``RoomPartition_hasOneClass``);
 * - Printing the disjoint-set (``RoomPartition_print``), used mostly for
 *   debugging;
 * - Freeing the disjoint-set (``RoomPartition_free``).
 *
 * @author Alexandre Blondin Masse
 */
#ifndef ROOM_PARTITION_H
#define ROOM_PARTITION_H

#include <stdbool.h>

// --------------- //
// Data structures //
// --------------- //

struct Element {
    struct Element *parent;
    unsigned int rank;
};

struct RoomPartition {
    struct Element **elements;
    unsigned int numRows;
    unsigned int numColumns;
    unsigned int numClasses;
};


/**
 * Creates the trivial partition for the the rooms of the given maze size.
 *
 * The trivial partition is the partition where each room is single in its own
 * class.
 *
 * Warning: Creates a memory leak if the partition is not freed.
 *
 * @param numRows     The number of rows in the maze
 * @param numColumns  The number of columns in the maze
 * @return            The resulting partition
 */
struct RoomPartition RoomPartition_create(unsigned int numRows,
                                          unsigned int numColumns);

/**
 * Merges the two classes of the given rooms in the partition.
 *
 * @param partition  The partition of the rooms
 * @param room1i     The row of the first room
 * @param room1j     The column of the first room
 * @param room2i     The row of the second room
 * @param room2j     The column of the second room
 */
void RoomPartition_merge(struct RoomPartition *partition,
                         unsigned int room1i,
                         unsigned int room1j,
                         unsigned int room2i,
                         unsigned int room2j);

/**
 * Returns true if and only if the two rooms are in the same partition.
 *
 * @param partition  The partition of the rooms
 * @param room1i     The row of the first room
 * @param room1j     The column of the first room
 * @param room2i     The row of the second room
 * @param room2j     The column of the second room
 * @param            True if and only if the two rooms are in the same
 *                   partition
 */
bool RoomPartition_areInSameClass(const struct RoomPartition *partition,
                                  unsigned int room1i,
                                  unsigned int room1j,
                                  unsigned int room2i,
                                  unsigned int room2j);

/**
 * Returns the number of classes in the partition.
 *
 * @param partition  The partition of the rooms
 * @return           The number of classes in the partition
 */
unsigned int RoomPartition_numberOfClasses(const struct RoomPartition *partition);

/**
 * Returns the number of classes in the partition.
 *
 * @param partition  The partition of the rooms
 * @return           The number of classes in the partition
 */
bool RoomPartition_hasOneClass(const struct RoomPartition *partition);

/**
 * Prints the partition on stdout.
 *
 * @param partition  The partition of the rooms
 */
void RoomPartition_print(const struct RoomPartition *partition);

/**
 * Frees the given partition.
 *
 * @param partition  The partition of the rooms
 */
void RoomPartition_free(struct RoomPartition *partition);

#endif
