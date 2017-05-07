#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void internalError(const char *message) {
    fprintf(stderr, "Internal error: %s\n", message);
    exit(EXIT_FAILURE);
}

void sysError(const char *message) {
    fprintf(stderr, "System error!\n");
    perror(message);
    exit(EXIT_FAILURE);
}

void syntaxError(const char *message, int srcLineNr) {
    fprintf(stderr, "Syntax error: %s\n", message);
    fprintf(stderr, "              at line %d\n", srcLineNr);
    exit(EXIT_FAILURE);
}
