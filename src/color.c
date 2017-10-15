/**
 * File color.c
 *
 * Implements color.h.
 *
 * @author Alexandre Blondin Masse
 */
#include "color.h"
#include <string.h>

struct Color Color_colorFromName(const char *colorName) {
    struct Color color;
    if (strcmp(colorName, "black") == 0) {
        color.r = 0.000; color.g = 0.000; color.b = 0.000;
    } else if (strcmp(colorName, "gray") == 0) {
        color.r = 0.500; color.g = 0.500; color.b = 0.500;
    } else if (strcmp(colorName, "silver") == 0) {
        color.r = 0.750; color.g = 0.750; color.b = 0.750;
    } else if (strcmp(colorName, "white") == 0) {
        color.r = 0.000; color.g = 0.000; color.b = 0.000;
    } else if (strcmp(colorName, "maroon") == 0) {
        color.r = 0.500; color.g = 0.000; color.b = 0.000;
    } else if (strcmp(colorName, "red") == 0) {
        color.r = 1.000; color.g = 0.000; color.b = 0.000;
    } else if (strcmp(colorName, "olive") == 0) {
        color.r = 0.500; color.g = 0.500; color.b = 0.000;
    } else if (strcmp(colorName, "yellow") == 0) {
        color.r = 1.000; color.g = 1.000; color.b = 0.000;
    } else if (strcmp(colorName, "green") == 0) {
        color.r = 0.000; color.g = 0.500; color.b = 0.000;
    } else if (strcmp(colorName, "lime") == 0) {
        color.r = 0.000; color.g = 1.000; color.b = 0.000;
    } else if (strcmp(colorName, "teal") == 0) {
        color.r = 0.000; color.g = 0.500; color.b = 0.500;
    } else if (strcmp(colorName, "aqua") == 0) {
        color.r = 0.000; color.g = 1.000; color.b = 1.000;
    } else if (strcmp(colorName, "navy") == 0) {
        color.r = 0.000; color.g = 0.000; color.b = 0.500;
    } else if (strcmp(colorName, "blue") == 0) {
        color.r = 0.000; color.g = 0.000; color.b = 1.000;
    } else if (strcmp(colorName, "purple") == 0) {
        color.r = 0.500; color.g = 0.000; color.b = 0.500;
    } else if (strcmp(colorName, "fuchsia") == 0) {
        color.r = 1.000; color.g = 0.000; color.b = 1.000;
    }
    return color;
}

bool Color_isNamedColor(const char *colorName) {
    return strcmp(colorName, "black")   == 0 ||
           strcmp(colorName, "gray")    == 0 ||
           strcmp(colorName, "silver")  == 0 ||
           strcmp(colorName, "white")   == 0 ||
           strcmp(colorName, "maroon")  == 0 ||
           strcmp(colorName, "red")     == 0 ||
           strcmp(colorName, "olive")   == 0 ||
           strcmp(colorName, "yellow")  == 0 ||
           strcmp(colorName, "green")   == 0 ||
           strcmp(colorName, "lime")    == 0 ||
           strcmp(colorName, "teal")    == 0 ||
           strcmp(colorName, "aqua")    == 0 ||
           strcmp(colorName, "navy")    == 0 ||
           strcmp(colorName, "blue")    == 0 ||
           strcmp(colorName, "purple")  == 0 ||
           strcmp(colorName, "fuchsia") == 0;
}
