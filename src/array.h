/**
 * File array.h
 *
 * Implements a dynamic array whose elements are pairs of unsigned integers.
 * The only supported operations are the following:
 *
 * - Creation of an empty array (`Array_create`);
 * - Appending an element to the end (`Array_append`);
 * - Reading the i-th element (`Array_get`);
 * - Printing an array to stdout (`Array_print`);
 * - Deleting an array (`Array_delete`).
 *
 * @author Alexandre Blondin Masse
 */
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
 * @param array  The array to delete
 */
void Array_delete(struct Array *array);

#endif
