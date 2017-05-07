#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void syntaxError(const char *message, int srcLineNr) {
    fprintf(stderr, "Syntax error: %s\n", message);
    fprintf(stderr, "              at line %d\n", srcLineNr);
    exit(EXIT_FAILURE);
}
