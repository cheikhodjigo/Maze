/**
 * File test_partition.c
 *
 * Testing the ``room_partition`` module with CUnit.
 *
 * @author Alexandre Blondin Masse
 */
#include "room_partition.h"
#include "CUnit/Basic.h"

void test_basicPartition() {
    struct RoomPartition partition = RoomPartition_create(4, 3);
    CU_ASSERT(RoomPartition_numberOfClasses(&partition) == 12);
    RoomPartition_merge(&partition, 0, 0, 0, 1);
    CU_ASSERT(RoomPartition_areInSameClass(&partition, 0, 0, 0, 1));
    RoomPartition_merge(&partition, 0, 1, 0, 2);
    CU_ASSERT(RoomPartition_areInSameClass(&partition, 0, 1, 0, 2));
    CU_ASSERT(RoomPartition_areInSameClass(&partition, 0, 0, 0, 2));
    CU_ASSERT(RoomPartition_numberOfClasses(&partition) == 10);
    RoomPartition_free(&partition);
}

void test_onlyOneClassPartition() {
    struct RoomPartition partition = RoomPartition_create(2, 2);
    CU_ASSERT(RoomPartition_numberOfClasses(&partition) == 4);
    RoomPartition_merge(&partition, 0, 0, 0, 1);
    RoomPartition_merge(&partition, 0, 1, 1, 1);
    RoomPartition_merge(&partition, 0, 1, 1, 0);
    CU_ASSERT(RoomPartition_numberOfClasses(&partition) == 1);
    CU_ASSERT(RoomPartition_numberOfClasses(&partition) == 1);
    CU_ASSERT(RoomPartition_hasOneClass(&partition));
    RoomPartition_free(&partition);
}

int main() {
    CU_pSuite pSuite = NULL;
    if (CU_initialize_registry() != CUE_SUCCESS )
        return CU_get_error();

    pSuite = CU_add_suite("Testing partition", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Creating basic partition",
                    test_basicPartition) == NULL ||
        CU_add_test(pSuite, "Only one class partition",
                    test_onlyOneClassPartition) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
