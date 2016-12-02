/**
 * File array.c
 *
 * Implementation of array.h.
 *
 * @author Alexandre Blondin Masse
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "array.h"

struct Array *Array_create() {
    struct Array *array = (struct Array*)malloc(sizeof(struct Array));
    array->values = (struct uiPair*)malloc(sizeof(struct uiPair));
    array->length = 0;
    array->capacity = 1;
    return array;
}

void Array_append(struct Array *array, const struct uiPair *pair) {
    if (array->length >= array->capacity) {
        array->capacity *= 2;
        struct uiPair *newArray = realloc(array->values, array->capacity * sizeof(struct uiPair));
        array->values = newArray;
    }
    array->values[array->length] = *pair;
    ++array->length;
}

const struct uiPair *Array_get(const struct Array *array, unsigned int i) {
    assert(i < array->length);
    return &array->values[i];
}

void Array_print(const struct Array *array) {
    unsigned int i;
    printf("[");
    for (i = 0; i < array->length; ++i) {
        printf(" (%d, %d)", array->values[i].first, array->values[i].second);
    }
    printf(" ]");
}

void Array_delete(struct Array *array) {
    free(array->values);
    free(array);
}
