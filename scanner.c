#include "scanner.h"

// Read-in file buffer
char **lines;

// Scanner cursor position
unsigned int srcLineNr = 0;
unsigned int colPos = 0;

// Last read and next tokens
token currentToken;
token nextToken;

// True if we reached EOF while advancing
bool done = false;
unsigned int readLines = 0;

/*
Reads lines from the given file into an array of lines.
*/
void initScanner(FILE *file) {

    // Read lines into **lines buffer
    int numLines = NUM_LINES_DEFAULT;
    lines = (char **) calloc(sizeof(char *), numLines);

    int lineSz = LINE_BUFFER_DEFAULT; // max size of line buffer
    lines[0] = (char *) calloc(sizeof(char), lineSz);      // initialize first line buffer

    char currentChar;   // current character from file
    int c = 0;          // column position in current line
    int lineNr = 0;     // current src line number

    while (!feof(file)) {

        currentChar = fgetc(file);

        if (currentChar == '\n') {
            lines[lineNr][c] = '\0';                        // null terminate current line
            lineNr++;                                       // advance to next line
            lines[lineNr] = (char *) calloc(sizeof(char), lineSz);   // allocate space for our new line
            c = 0;
        } else {
            lines[lineNr][c++] = currentChar; // add character to current line
        }

        if (c >= lineSz) {
            // if we run out of room in our current line, double the size.
            lineSz *= 2;
            lines[lineNr] = (char *) realloc(lines[lineNr], sizeof(char) * lineSz);
        }

        if (lineNr >= numLines) {
            // if we run out of room for lines, double the max # of lines.
            numLines *= 2;
            lines = (char **) realloc(lines, sizeof(char *) * numLines);
        }

    }

    // mark last line as done with NULL
    lines[lineNr] = NULL;
    readLines = lineNr;

}

void testScanner() {

    printf("Read %d line(s)\n", readLines);

    printf("========================\n");
    int l = 0;
    while (lines[l] != NULL) {
        printf("%s\n", lines[l++]);
    }
    printf("========================\n");

    char *token;

    while ((token = getNext()) != NULL) {
        printf("%s\n", currentToken.tokenStr);
        //printf("%s\n", nextToken.tokenStr);
    }

}

/*
Advances the scanner's internal cursor to the next token, updating the
currentToken and nextToken appropriately.
*/
char * getNext() {

    currentToken.tokenStr = readNextToken(true);
    //nextToken.tokenStr = readNextToken(false);

    return currentToken.tokenStr;

}

void classifyToken(token *tok) {

    if (strcmp(tok->tokenStr, ";") == 0) {

    } else if (strcmp(tok->tokenStr, "=") == 0) {

    } else if (strcmp(tok->tokenStr, "if") == 0) {

    } else if (strcmp(tok->tokenStr, "while") == 0) {

    } else if (strcmp(tok->tokenStr, "for") == 0) {

    } else if (strcmp(tok->tokenStr, "==") == 0) {

    } else if (strcmp(tok->tokenStr, "!=") == 0) {

    } else if (strcmp(tok->tokenStr, ">") == 0) {

    } else if (strcmp(tok->tokenStr, "<") == 0) {

    } else if (strcmp(tok->tokenStr, ">=") == 0) {

    } else if (strcmp(tok->tokenStr, "<=") == 0) {

    } else if (strcmp(tok->tokenStr, "+") == 0) {

    } else if (strcmp(tok->tokenStr, "-") == 0) {

    } else if (strcmp(tok->tokenStr, "/") == 0) {

    } else if (strcmp(tok->tokenStr, "*") == 0) {

    } else if (strcmp(tok->tokenStr, "+=") == 0) {

    } else if (strcmp(tok->tokenStr, "-=") == 0) {

    } else if (strcmp(tok->tokenStr, "*=") == 0) {

    } else if (strcmp(tok->tokenStr, "/=") == 0) {

    } else if (strcmp(tok->tokenStr, "%=") == 0) {

    } else if (strcmp(tok->tokenStr, "(") == 0) {

    } else if (strcmp(tok->tokenStr, ")") == 0) {

    } else if (strcmp(tok->tokenStr, "[") == 0) {

    } else if (strcmp(tok->tokenStr, "]") == 0) {

    } else if (strcmp(tok->tokenStr, "!") == 0) {

    } else if (strcmp(tok->tokenStr, "@") == 0) {

    } else if (strcmp(tok->tokenStr, "#") == 0) {

    } else if (strcmp(tok->tokenStr, "%") == 0) {

    } else if (strcmp(tok->tokenStr, "^") == 0) {

    } else if (strcmp(tok->tokenStr, "&") == 0) {

    } else if (strcmp(tok->tokenStr, ":") == 0) {

    } else {

    }

}

/*
Allocates space for and returns the next token string.
*/
char * readNextToken(bool advance) {

    if (done) {
        return NULL;
    }

    int savedLineNr = srcLineNr;
    int savedColPos = colPos;

    // Advances internal cursor until we find a non-whitespace char
    while (strchr(WHITESPACE, lines[srcLineNr][colPos]) && !done) {
        //printf("skipped whitespace at %d, %d\n", srcLineNr, colPos);
        advanceCursor();
    }

    int i = 0;
    int strSz = TOKEN_DEFAULT_LEN;
    char *tokenStr = (char *) calloc(sizeof(char), strSz);

    while (!done) {

        if (i >= strSz) {
            strSz *= 2;
            tokenStr = (char *) realloc(tokenStr, sizeof(char) * strSz);
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

    if (!advance) {
        srcLineNr = savedLineNr;
        colPos = savedColPos;
    }

    //printf("returning: %s\n", tokenStr);
    return tokenStr;

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
            done = true;
        }

    }

    //printf("advanced to line %d, %d\n", srcLineNr, colPos);

}
