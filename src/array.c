#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "array.h"

struct Array Array_create() {
    struct Array array;
    array.values = (struct uiPair*)malloc(sizeof(struct uiPair));
    array.length = 0;
    array.capacity = 1;
    return array;
}

void Array_append(struct Array *array, const struct uiPair *pair) {
    if (array->length >= array->capacity) {
        array->capacity *= 2;
        realloc(array->values, array->capacity * sizeof(struct uiPair));
    }
    array->values[array->length] = *pair;
    ++array->length;
}

const struct uiPair *Array_get(const struct Array *array, unsigned int i) {
    assert(0 <= i && i < array->length);
    return &array->values[i];
}

void Array_print(const struct Array *array) {
    int i;
    printf("[");
    for (i = 0; i < array->length; ++i) {
        printf(" (%d, %d)", array->values[i].i, array->values[i].j);
    }
    printf(" ]");
}

void Array_delete(struct Array *array) {
    free(array->values);
}
