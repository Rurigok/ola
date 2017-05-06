#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

void usage(char *progname, char *message) {

    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Usage: %s filename\n", progname);
    exit(EXIT_FAILURE);

}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        usage(argv[0], "Inappropriate number of arguments");
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Open file");
    }

    initScanner(file);
    testScanner();

}
