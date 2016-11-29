/**
 * File room_partition.c
 *
 * Implements room_partition.h.
 *
 * This is a classical implementation, using both the rank and compressed path
 * heuristics, yielding an almost constant amortized time for the ``merge`` and
 * ``find`` operations. See the Wikipedia entry for more details.
 *
 * @author Alexandre Blondin Masse
 */
#include <stdlib.h>
#include <stdio.h>
#include "room_partition.h"

// ----------------- //
// Private functions //
// ----------------- //

struct Element *RoomPartition_parent(const struct RoomPartition *partition,
                                     struct Element *element) {
    if (element != element->parent) {
        element->parent = RoomPartition_parent(partition, element->parent);
    }
    return element->parent;
}

// ---------------- //
// Public functions //
// ---------------- //

struct RoomPartition RoomPartition_create(unsigned int numRows,
                                          unsigned int numColumns) {
    struct RoomPartition partition;
    partition.elements = (struct Element**)malloc(numRows * sizeof(struct Element*));
    unsigned int i, j;
    for (i = 0; i < numRows; ++i) {
        partition.elements[i] = (struct Element*)malloc(numColumns * sizeof(struct Element));
        for (j = 0; j < numColumns; ++j) {
            partition.elements[i][j].rank = 0;
            partition.elements[i][j].parent = &partition.elements[i][j];
        }
    }
    partition.numRows = numRows;
    partition.numColumns = numColumns;
    partition.numClasses = numRows * numColumns;
    return partition;
}

void RoomPartition_merge(struct RoomPartition *partition,
                         unsigned int room1i,
                         unsigned int room1j,
                         unsigned int room2i,
                         unsigned int room2j) {
    struct Element *representant1, *representant2;
    representant1 = RoomPartition_parent(partition,
                                         &partition->elements[room1i][room1j]);
    representant2 = RoomPartition_parent(partition,
                                         &partition->elements[room2i][room2j]);
    if (representant1 != representant2) {
        --partition->numClasses;
        if (representant1->rank > representant2->rank) {
            representant2->parent = representant1;
        } else {
            representant1->parent = representant2;
            if (representant1->rank == representant2->rank) {
                ++representant2->rank;
            }
        }
    }
}

bool RoomPartition_areInSameClass(const struct RoomPartition *partition,
                                  unsigned int room1i,
                                  unsigned int room1j,
                                  unsigned int room2i,
                                  unsigned int room2j) {
    struct Element *representant1, *representant2;
    representant1 = RoomPartition_parent(partition,
                                         &partition->elements[room1i][room1j]);
    representant2 = RoomPartition_parent(partition,
                                         &partition->elements[room2i][room2j]);
    return representant1 == representant2;
}

unsigned int RoomPartition_numberOfClasses(const struct RoomPartition *partition) {
    return partition->numClasses;
}

bool RoomPartition_hasOneClass(const struct RoomPartition *partition) {
    return RoomPartition_numberOfClasses(partition) == 1;
}

void RoomPartition_print(const struct RoomPartition *partition) {
    printf("Partition of %d classes\n", RoomPartition_numberOfClasses(partition));
}

void RoomPartition_free(struct RoomPartition *partition) {
    unsigned int i;
    for (i = 0; i < partition->numRows; ++i) {
        free(partition->elements[i]);
    }
    free(partition->elements);
}
