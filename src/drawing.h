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
 * @param wallsColor      The name of the walls color
 *                        (one of the 16 basic colors)
 * @param withSolution    If true, the solution is drawn as well
 */
void Drawing_drawMaze(const struct Maze* maze,
                      const char *outputFilename,
                      const char *wallsColor,
                      bool withSolution);

#endif
