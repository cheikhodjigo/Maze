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

char *strdupLower(const char *s) {
    char *t = strdup(s);
    int i = 0;
    while (t[i] != '\0') {
        t[i] = tolower(t[i]);
        ++i;
    }
    return t;
}
