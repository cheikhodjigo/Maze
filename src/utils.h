#ifndef UTILS_H
#define UTILS_H

/**
 * Copies the string to lower case
 *
 * @param s       The resulting string
 * @param t       The string to be copied
 * @param length  The maximum length of the string
 */
void strncpyLower(char *s, const char *t, int length);

/**
 * Duplicates the string to lower case
 *
 * @param s  The string to be copied
 * @return   The resulting string
 */
char *strdupLower(const char *s);

#endif
