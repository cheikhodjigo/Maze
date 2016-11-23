#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_args.h"

int main(int argc, char **argv) {
    struct Arguments arguments = parseArguments(argc, argv);
    return arguments.status;
}
