#include "array.h"

int main() {
    struct Array *array = Array_create();
    struct uiPair pair;
    pair.first = 2; pair.second = 3;
    Array_append(array, &pair);
    pair.first = 5; pair.second = 7;
    Array_append(array, &pair);
    Array_print(array);
    Array_delete(array);
    return 0;
}
