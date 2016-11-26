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

#endif
