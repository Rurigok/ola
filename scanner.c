#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

// Read-in file buffer
extern char **lines;

// Scanner cursor position
extern int srcLineNr;
extern int colPos;

// Last read and next tokens
extern token currentToken;
extern token nextToken;

// True if we reached EOF while advancing
int done;
int readLines;

/*
Reads lines from the given file into an array of lines.
*/
void initScanner(FILE *file) {

    // Initialize scanner state
    srcLineNr = 0;
    colPos = 0;
    done = 0;

    // Read lines into **lines buffer
    int numLines = NUM_LINES_DEFAULT;
    lines = calloc(sizeof(char *), numLines);

    int lineSz = LINE_BUFFER_DEFAULT; // max size of line buffer
    char *line = malloc(sizeof(char) * lineSz);      // current line buffer

    char currentChar;   // current character from file
    int c = 0;          // column position in current line
    int lineNr = 0;     // current src line number

    while (!feof(file)) {

        currentChar = fgetc(file);

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
    readLines = lineNr;

    printf("Read %d line(s)\n", readLines);

}

/*
Advances the scanner's internal cursor to the next token, updating the
currentToken and nextToken appropriately.
*/
char * getNext() {



}

char * readNextToken() {

    char c = lines[srcLineNr][colPos];

}

/*
If the internal cursor is on a whitespace character, this function advances
the cursor until a non-whitespace character is found.
Otherwise, it does nothing.

Post-condition: internal cursor is on a non-whitespace character or EOF
*/
void skipWhitespace() {

    while (strchr(WHITESPACE, lines[srcLineNr][colPos])) {
        advanceCursor();
    }

}

/*
Advances the scanner's internal cursor by one character
*/
void advanceCursor() {

    colPos++;

    if (colPos == strlen(lines[srcLineNr])) {
        // We've reached the end of this line
        srcLineNr++;

        if (lines[srcLineNr] == NULL) {
            // We're out of lines
            done = 1;
        }

    }

}
