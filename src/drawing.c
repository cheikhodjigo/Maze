#include <cairo.h>
#include "maze.h"

#define ROOM_WIDTH 30
#define ROOM_HEIGHT 30
#define ROW_OFFSET 2
#define COL_OFFSET 2

void Drawing_drawMaze(const struct Maze *maze) {
    cairo_surface_t *surface =
		cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
		COL_OFFSET + maze->numCols * (ROOM_WIDTH + COL_OFFSET),
		ROW_OFFSET + maze->numRows * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_t *cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 0, 0, 1);
	for (unsigned int i = 0; i < maze->numRows; ++i) {
		for (unsigned int j = 0; j < maze->numCols; ++j) {
    		cairo_rectangle(cr,
							COL_OFFSET + j * (ROOM_WIDTH + COL_OFFSET),
							ROW_OFFSET + i * (ROOM_WIDTH + ROW_OFFSET),
							ROOM_WIDTH, ROOM_HEIGHT);
    		cairo_fill(cr);
		}
	}
    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, "maze.png");
    cairo_surface_destroy(surface);
}
