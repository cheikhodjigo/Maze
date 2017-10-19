/**
 * File test_maze.c
 *
 * Testing the ``maze`` module with CUnit.
 *
 * @author Alexandre Blondin Masse
 */
#include "maze.h"
#include "CUnit/Basic.h"

void test_randomMaze() {
    struct Arguments arguments = {.numRows    = 3,
                                  .numCols    = 4,
                                  .startRoomi = 0,
                                  .startRoomj = 0,
                                  .endRoomi   = 2,
                                  .endRoomj   = 3};
    struct Maze *maze = Maze_randomMaze(&arguments);
    CU_ASSERT(maze != NULL);
    CU_ASSERT(maze->numRows == 3);
    CU_ASSERT(maze->numCols == 4);
    CU_ASSERT(Maze_areRoomsConsistent(maze));
    CU_ASSERT(RoomPartition_hasOneClass(&maze->partition));
    Maze_free(maze);
}

void test_randomMaze2() {
    struct Arguments arguments = {.numRows    = 7,
                                  .numCols    = 3,
                                  .startRoomi = 0,
                                  .startRoomj = 0,
                                  .endRoomi   = 6,
                                  .endRoomj   = 2};
    struct Maze *maze = Maze_randomMaze(&arguments);
    CU_ASSERT(maze != NULL);
    CU_ASSERT(maze->numRows == 7);
    CU_ASSERT(maze->numCols == 3);
    CU_ASSERT(Maze_areRoomsConsistent(maze));
    CU_ASSERT(RoomPartition_hasOneClass(&maze->partition));
    Maze_free(maze);
}

void test_path() {
    struct Arguments arguments = {.numRows    = 7,
                                  .numCols    = 3,
                                  .startRoomi = 0,
                                  .startRoomj = 0,
                                  .endRoomi   = 6,
                                  .endRoomj   = 2};
    struct Maze *maze = Maze_randomMaze(&arguments);
    CU_ASSERT(maze != NULL);
    CU_ASSERT(maze->path->length <= 7 * 3);
    Maze_free(maze);
}

int main() {
    CU_pSuite pSuite = NULL;
    if (CU_initialize_registry() != CUE_SUCCESS )
        return CU_get_error();

    pSuite = CU_add_suite("Testing maze", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(pSuite, "Basic maze", test_randomMaze) == NULL ||
        CU_add_test(pSuite, "Another basic maze", test_randomMaze2) == NULL ||
        CU_add_test(pSuite, "Check path", test_path) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
