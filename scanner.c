#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

// Read-in file buffer
char **lines;

// Scanner cursor position
int srcLineNr;
int colPos;

// Last read and next tokens
token currentToken;
token nextToken;

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
    lines[0] = calloc(sizeof(char), lineSz);      // initialize first line buffer

    char currentChar;   // current character from file
    int c = 0;          // column position in current line
    int lineNr = 0;     // current src line number

    while (!feof(file)) {

        currentChar = fgetc(file);

        if (currentChar == '\n') {
            lines[lineNr][c] = '\0';                        // null terminate current line
            lineNr++;                                       // advance to next line
            lines[lineNr] = calloc(sizeof(char), lineSz);   // allocate space for our new line
            c = 0;
        } else {
            lines[lineNr][c++] = currentChar; // add character to current line
        }

        if (c >= lineSz) {
            // if we run out of room in our current line, double the size.
            lineSz *= 2;
            lines[lineNr] = realloc(lines[lineNr], sizeof(char) * lineSz);
        }

        if (lineNr >= numLines) {
            // if we run out of room for lines, double the max # of lines.
            numLines *= 2;
            lines = realloc(lines, sizeof(char *) * numLines);
        }

    }

    // mark last line as done with NULL
    lines[lineNr] = NULL;
    readLines = lineNr;

    printf("Read %d line(s)\n", readLines);

    printf("========================\n");
    int l = 0;
    while (lines[l] != NULL) {
        printf("%s\n", lines[l++]);
    }
    printf("========================\n");

    char *token;

    while ((token = readNextToken()) != NULL) {
        printf("token: %s\n", token);
    }

}

/*
Advances the scanner's internal cursor to the next token, updating the
currentToken and nextToken appropriately.
*/
char * getNext() {



}

char * readNextToken() {

    if (done) {
        return NULL;
    }

    skipWhitespace();

    int i = 0;
    int strSz = TOKEN_DEFAULT_LEN;
    char *tokenStr = calloc(sizeof(char), strSz);

    while (!done) {

        if (i >= strSz) {
            strSz *= 2;
            tokenStr = realloc(tokenStr, strSz);
        }

        //printf("char is: %c ... ", lines[srcLineNr][colPos]);

        if (strchr(DELIMITERS, lines[srcLineNr][colPos])) {

            //printf("found delim ...");

            if (strlen(tokenStr) == 0) {
                //printf("first char was delim, copied ... ");
                memcpy(&tokenStr[i++], &lines[srcLineNr][colPos], 1);
                advanceCursor();
            }

            break;
        } else {

            //printf("is not delim, copied ... ");
            memcpy(&tokenStr[i++], &lines[srcLineNr][colPos], 1);
            advanceCursor();

        }

    }

    //printf("returning: %s\n", tokenStr);
    return tokenStr;

}

/*
If the internal cursor is on a whitespace character, this function advances
the cursor until a non-whitespace character is found.
Otherwise, it does nothing.

Post-condition: internal cursor is on the first non-whitespace character found or EOF
*/
void skipWhitespace() {

    while (strchr(WHITESPACE, lines[srcLineNr][colPos]) && !done) {
        //printf("skipped whitespace at %d, %d\n", srcLineNr, colPos);
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
        colPos = 0;

        if (lines[srcLineNr] == NULL) {
            // We're out of lines
            done = 1;
        }

    }

    //printf("advanced to line %d, %d\n", srcLineNr, colPos);

}
