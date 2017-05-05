#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

token currentToken;
token nextToken;
char **lines;

/*
Reads lines from the given file into an array of lines.
*/
void initScanner(FILE *file) {

    int numLines = NUM_LINES_DEFAULT;
    lines = calloc(sizeof(char *), numLines);

    int lineSz = LINE_BUFFER_DEFAULT; // max size of line buffer
    char *line = malloc(sizeof(char) * lineSz);      // current line buffer

    char currentChar;   // current character from file
    int c = 0;          // column position in current line
    int lineNr = 0;     // current src line number

    while (!feof(file)) {

        currentChar = fgetc(file);
        //printf("lineNr: %d, col: %d, char: %c\n", lineNr, c, currentChar);

        if (currentChar == '\n') {
            line[c] = '\0'; // null terminate current line
            lines[lineNr++] = line; // add current line to line buffer
            line = malloc(sizeof(char) * lineSz);   // allocate space for next line
            c = 0;
        } else {
            line[c++] = currentChar; // add character to current line
        }

        if (c >= lineSz) {
            // if we run out of room in our current line, double the size.
            lineSz *= 2;
            line = realloc(line, sizeof(char) * lineSz);
        }

        if (lineNr >= numLines) {
            // if we run out of room for lines, double the max # of lines.
            numLines *= 2;
            lines = realloc(lines, sizeof(char *) * numLines);
        }

    }

    // mark last line as done with NULL
    lines[++lineNr] = NULL;

    // printf("===============================\n");
    // char *cline;
    // int i = 0;
    // while (lines[i] != NULL) {
    //     printf("%s\n", lines[i++]);
    // }

}

/*
*/
char * getNext() {

}
