#include <cairo.h>
#include "maze.h"

#define ROOM_WIDTH 30
#define ROOM_HEIGHT 30
#define ROW_OFFSET 2
#define COL_OFFSET 2

void Drawing_drawRoom(cairo_t *cr,
                      const struct Room *room,
                      unsigned int i,
                      unsigned int j) {
    // Top wall
    cairo_set_line_width(cr, 1);
    cairo_move_to(cr,
                  j * (ROOM_WIDTH + COL_OFFSET),
                  i * (ROOM_WIDTH + ROW_OFFSET));
    cairo_set_source_rgba(cr, 0, 0, 0,
                          room->up ? 0.0 : 1.0);
    cairo_line_to(cr,
                  (j + 1) * (ROOM_WIDTH + COL_OFFSET),
                  i * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_stroke(cr);
    // Left wall
    cairo_set_line_width(cr, 1);
    cairo_move_to(cr,
                  j * (ROOM_WIDTH + COL_OFFSET),
                  i * (ROOM_WIDTH + ROW_OFFSET));
    cairo_set_source_rgba(cr, 0, 0, 0,
                          room->left ? 0.0 : 1.0);
    cairo_line_to(cr,
                  j * (ROOM_WIDTH + COL_OFFSET),
                  (i + 1) * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_stroke(cr);
    // Right wall
    cairo_set_line_width(cr, 1);
    cairo_move_to(cr,
                  (j + 1) * (ROOM_WIDTH + COL_OFFSET),
                  i * (ROOM_WIDTH + ROW_OFFSET));
    cairo_set_source_rgba(cr, 0, 0, 0,
                          room->right ? 0.0 : 1.0);
    cairo_line_to(cr,
                  (j + 1) * (ROOM_WIDTH + COL_OFFSET),
                  (i + 1) * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_stroke(cr);
    // Down wall
    cairo_set_line_width(cr, 1);
    cairo_move_to(cr,
                  j * (ROOM_WIDTH + COL_OFFSET),
                  (i + 1) * (ROOM_WIDTH + ROW_OFFSET));
    cairo_set_source_rgba(cr, 0, 0, 0,
                          room->down ? 0.0 : 1.0);
    cairo_line_to(cr,
                  (j + 1) * (ROOM_WIDTH + COL_OFFSET),
                  (i + 1) * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_stroke(cr);
}

void Drawing_drawMaze(const struct Maze *maze) {
    cairo_surface_t *surface =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
        COL_OFFSET + maze->numCols * (ROOM_WIDTH + COL_OFFSET),
        ROW_OFFSET + maze->numRows * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_t *cr = cairo_create(surface);

    unsigned int i, j;
    for (i = 0; i < maze->numRows; ++i) {
        for (j = 0; j < maze->numCols; ++j) {
            Drawing_drawRoom(cr, &maze->rooms[i][j], i, j);
        }
    }
    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, "maze.png");
    cairo_surface_destroy(surface);
}
