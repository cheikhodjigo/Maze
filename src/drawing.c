/**
 * File drawing.c
 *
 * Draws a maze in a PNG file, by drawing each of its rooms (i.e. cells)
 * individually.
 *
 * The Cairo library is used to produce the image.
 *
 * @author Alexandre Blondin Masse
 */
#include "drawing.h"
#include "color.h"
#include <string.h>
#include <cairo.h>

#define ROOM_WIDTH 30
#define ROOM_HEIGHT 30
#define ROW_OFFSET 2
#define COL_OFFSET 2
#define PATH_WIDTH 1

// ----------------- //
// Private functions //
// ----------------- //

/**
 * Draws the given room on a surface.
 *
 * @param cr    The Cairo surface on which we draw
 * @param room  The room to draw
 * @param i     The row number of the room
 * @param j     The column number of the room
 */
void Drawing_drawRoom(cairo_t *cr,
                      const struct Room *room,
                      unsigned int i,
                      unsigned int j,
                      const struct Color *color) {
    // Top wall
    cairo_set_line_width(cr, ROW_OFFSET);
    cairo_move_to(cr,
                  j * (ROOM_WIDTH + COL_OFFSET),
                  i * (ROOM_WIDTH + ROW_OFFSET));
    cairo_set_source_rgba(cr, color->r, color->g, color->b,
                          room->up ? 0.0 : 1.0);
    cairo_line_to(cr,
                  (j + 1) * (ROOM_WIDTH + COL_OFFSET),
                  i * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_stroke(cr);
    // Left wall
    cairo_set_line_width(cr, COL_OFFSET);
    cairo_move_to(cr,
                  j * (ROOM_WIDTH + COL_OFFSET),
                  i * (ROOM_WIDTH + ROW_OFFSET));
    cairo_set_source_rgba(cr, color->r, color->g, color->b,
                          room->left ? 0.0 : 1.0);
    cairo_line_to(cr,
                  j * (ROOM_WIDTH + COL_OFFSET),
                  (i + 1) * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_stroke(cr);
    // Right wall
    cairo_set_line_width(cr, COL_OFFSET);
    cairo_move_to(cr,
                  (j + 1) * (ROOM_WIDTH + COL_OFFSET),
                  i * (ROOM_WIDTH + ROW_OFFSET));
    cairo_set_source_rgba(cr, color->r, color->g, color->b,
                          room->right ? 0.0 : 1.0);
    cairo_line_to(cr,
                  (j + 1) * (ROOM_WIDTH + COL_OFFSET),
                  (i + 1) * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_stroke(cr);
    // Down wall
    cairo_set_line_width(cr, ROW_OFFSET);
    cairo_move_to(cr,
                  j * (ROOM_WIDTH + COL_OFFSET),
                  (i + 1) * (ROOM_WIDTH + ROW_OFFSET));
    cairo_set_source_rgba(cr, color->r, color->g, color->b,
                          room->down ? 0.0 : 1.0);
    cairo_line_to(cr,
                  (j + 1) * (ROOM_WIDTH + COL_OFFSET),
                  (i + 1) * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_stroke(cr);
}

/**
 * Draws the solution of the maze.
 *
 * @param cr    The Cairo surface on which we draw
 * @param path  The path solution of the maze
 */
void Drawing_drawSolution(cairo_t *cr, const struct Array *path) {
    const struct uiPair *room;
    cairo_set_line_width(cr, PATH_WIDTH);
    room = Array_get(path, 0);
    cairo_move_to(cr,
                  (room->second + 0.5) * (COL_OFFSET + ROOM_WIDTH),
                  (room->first + 0.5) * (ROW_OFFSET + ROOM_HEIGHT));
    cairo_set_source_rgb(cr, 1, 0, 0);
    unsigned int k;
    for (k = 1; k < path->length; ++k) {
        room = Array_get(path, k);
        cairo_line_to(cr,
                      (room->second + 0.5) * (ROOM_WIDTH + COL_OFFSET),
                      (room->first + 0.5) * (ROOM_HEIGHT + ROW_OFFSET));
    }
    cairo_stroke(cr);
}

// ---------------- //
// Public functions //
// ---------------- //

void Drawing_drawMaze(const struct Maze *maze,
                      const struct Arguments *arguments) {
    cairo_surface_t *surface =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
        COL_OFFSET + maze->numCols * (ROOM_WIDTH + COL_OFFSET),
        ROW_OFFSET + maze->numRows * (ROOM_HEIGHT + ROW_OFFSET));
    cairo_t *cr = cairo_create(surface);

    unsigned int i, j;
    struct Color color = Color_colorFromName(arguments->wallsColor);
    for (i = 0; i < maze->numRows; ++i) {
        for (j = 0; j < maze->numCols; ++j) {
            Drawing_drawRoom(cr, &maze->rooms[i][j], i, j,
                             &color);
        }
    }
    if (arguments->withSolution) {
        Drawing_drawSolution(cr, maze->path);
    }
    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, arguments->outputFilename);
    cairo_surface_destroy(surface);
}
