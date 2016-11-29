/**
 * File drawing.h
 *
 * Draws image to PNG files. The Cairo library is used under the hood to
 * produce the image.
 *
 * @author Alexandre Blondin Masse
 */
#ifndef DRAWING_H
#define DRAWING_H

#include "maze.h"

/**
 * Produces a picture of a maze.
 *
 * @param maze            The maze whose picture is produced
 * @param outputFilename  The name of the output file
 *                        (should have a .png extension)
 */
void Drawing_drawMaze(const struct Maze* maze,
                      const char *outputFilename);

#endif
