/**
 * File utils.c
 *
 * Implements utils.h.
 *
 * @author Alexandre Blondin Masse
 */
#include <ctype.h>
#include <string.h>
#include "utils.h"

void strncpyLower(char *s, const char *t, int length) {
    strncpy(s, t, length);
    int i = 0;
    while (s[i] != '\0') {
        s[i] = tolower(s[i]);
        ++i;
    }
}
