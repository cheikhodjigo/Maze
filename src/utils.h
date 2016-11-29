/**
 * File utils.h
 *
 * Useful data structure and function. There are not related, but turn out very
 * useful in different parts of the program.
 *
 * @author Alexandre Blondin Masse
 */
#ifndef UTILS_H
#define UTILS_H

// --------------- //
// Data structures //
// --------------- //

struct uiPair {          // Unsigned integer pair
    unsigned int first;  // The first element
    unsigned int second; // The second element
};

/**
 * Copies the string to lower case.
 *
 * @param s       The resulting string
 * @param t       The string to be copied
 * @param length  The maximum length of the string
 */
void strncpyLower(char *s, const char *t, int length);

#endif
