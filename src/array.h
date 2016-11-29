#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

// Types
// -----

struct Array {
    struct uiPair *values; // The values
    unsigned int length;   // The number of elements
    unsigned int capacity; // The capacity
};

// ---------------- //
// Public functions //
// ---------------- //

/**
 * Creates an empty dynamic array and return it.
 *
 * Warning: Each call to ``arrayCreate()`` must be paired with a call to the
 * ``arrayDelete()`` function.
 *
 * @return  An empty array
 */
struct Array *Array_create();

/**
 * Appends an element to the end of an array.
 *
 * The array is automatically resized if its current size is not sufficient.
 *
 * @param array  The array
 * @param pair   The pair to append
 */
void Array_append(struct Array *array, const struct uiPair *pair);

/**
 * Returns the i-th pair in the array.
 *
 * @param array  The array
 * @param i      The index of the requested pair
 * @return       A pointer to the pair at index i
 */
const struct uiPair *Array_get(const struct Array *array, unsigned int i);

/**
 * Prints an array to stdout.
 *
 * @param array  The array to print
 */
void Array_print(const struct Array *array);

/**
 * Deletes an array.
 *
 * @param array  The array do delete
 */
void Array_delete(struct Array *array);

#endif
