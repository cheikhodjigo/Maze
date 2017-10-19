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
#include "parse_args.h"

/**
 * Produces a picture of a maze.
 *
 * @param maze       The maze whose picture is produced
 * @param arguments  The parameters of the maze
 */
void Drawing_drawMaze(const struct Maze* maze,
                      const struct Arguments *arguments);

#endif
