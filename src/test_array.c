/**
 * File test_array.c
 *
 * Testing the ``array`` module with CUnit.
 *
 * @author Alexandre Blondin Masse
 */
#include "array.h"
#include "CUnit/Basic.h"

void test_append() {
    struct Array *array = Array_create();
    struct uiPair pair;
    pair.first = 2; pair.second = 3;
    Array_append(array, &pair);
    pair.first = 5; pair.second = 7;
    Array_append(array, &pair);
    CU_ASSERT(array->length == 2);
    CU_ASSERT(Array_get(array, 0)->first == 2);
    CU_ASSERT(Array_get(array, 0)->second == 3);
    CU_ASSERT(Array_get(array, 1)->first == 5);
    CU_ASSERT(Array_get(array, 1)->second == 7);
    Array_delete(array);
}

int main() {
    CU_pSuite pSuite = NULL;
    if (CU_initialize_registry() != CUE_SUCCESS )
        return CU_get_error();

    pSuite = CU_add_suite("Testing append", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Appending to the array", test_append) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
