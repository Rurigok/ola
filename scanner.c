#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "scanner.h"
#include "error.h"

// Read-in file buffer
char **lines;

// Scanner cursor position
unsigned int srcLineNr = 0;
unsigned int colPos = 0;

// Last read and next tokens
token_t currentToken;
token_t nextToken;

unsigned int readLines = 0;

/*
Reads lines from the given file into an array of lines.
*/
void initScanner(FILE *file) {

    // Read lines into **lines buffer
    int numLines = NUM_LINES_DEFAULT;
    lines = (char **) calloc(sizeof(char *), numLines);

    if (lines == NULL) {
        sysError("calloc on lines buffer initialization");
    }

    int lineSz = LINE_BUFFER_DEFAULT; // max size of line buffer
    lines[0] = (char *) calloc(sizeof(char), lineSz);      // initialize first line buffer

    if (lines[0] == NULL) {
        sysError("calloc on first scanner line");
    }

    char currentChar;   // current character from file
    int c = 0;          // column position in current line
    int lineNr = 0;     // current src line number

    while (!feof(file)) {

        currentChar = fgetc(file);

        if (currentChar == '\n') {
            lines[lineNr][c] = '\0';                        // null terminate current line
            lineNr++;                                       // advance to next line
            lines[lineNr] = (char *) calloc(sizeof(char), lineSz);   // allocate space for our new line

            if (lines[lineNr] == NULL) {
                sysError("calloc");
            }

            c = 0;
        } else {
            lines[lineNr][c++] = currentChar; // add character to current line
        }

        if (c >= lineSz) {
            // if we run out of room in our current line, double the size.
            lineSz *= 2;

            char *temp = (char *) realloc(lines[lineNr], sizeof(char) * lineSz);
            if (temp == NULL) {
                sysError("realloc failed");
            }

            lines[lineNr] = temp;
        }

        if (lineNr >= numLines) {
            // if we run out of room for lines, double the max # of lines.
            numLines *= 2;

            char *temp = (char *) realloc(lines[lineNr], sizeof(char) * lineSz);
            if (temp == NULL) {
                sysError("realloc failed");
            }

            lines[lineNr] = temp;
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

void classifyToken(token_t *tok) {

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

    int savedLineNr = srcLineNr;
    int savedColPos = colPos;

    // Advances internal cursor until we find a non-whitespace char
    while (strchr(WHITESPACE, lines[srcLineNr][colPos])) {
        //printf("skipped whitespace at %d, %d\n", srcLineNr, colPos);

        if (lines[srcLineNr] == NULL) {
            return NULL;
        }

        advanceCursor();
    }

    int i = 0;
    int strSz = TOKEN_DEFAULT_LEN;
    char *tokenStr = (char *) calloc(sizeof(char), strSz);

    if (tokenStr == NULL) {
        sysError("calloc");
    }

    char openQuoteCh = 0;
    bool escaped = false;

    if (strchr(QUOTES, lines[srcLineNr][colPos])) {
        openQuoteCh = lines[srcLineNr][colPos];
        int openLineNr = srcLineNr;
        advanceCursor();

        while (true) {

            if (lines[srcLineNr] == NULL) {
                syntaxError("Unclosed string literal", openLineNr);
            }

            if (i >= strSz - 1) {
                strSz *= 2;
                tokenStr = (char *) realloc(tokenStr, sizeof(char) * strSz);
            }

            if (lines[srcLineNr][colPos] == openQuoteCh && !escaped) {
                advanceCursor();
                break;
            }

            if (lines[srcLineNr][colPos] == '\\') {
                //printf("Found escape sequence at %d %d\n", srcLineNr, colPos);
                escaped = true;
                advanceCursor();
                continue;
            }

            if (escaped) {
                if (strchr(ESCAPABLE, lines[srcLineNr][colPos])) {
                    //printf("Resolved escape sequence of %c\n", lines[srcLineNr][colPos]);
                    char replacement = resolveEscapeSequence(lines[srcLineNr][colPos]);
                    memcpy(&tokenStr[i++], &replacement, 1);
                    advanceCursor();
                    escaped = false;
                    continue;
                } else {
                    syntaxError("Invalid character in escape sequence", lines[srcLineNr][colPos]);
                }
            }

            memcpy(&tokenStr[i++], &lines[srcLineNr][colPos], 1);
            advanceCursor();

        }

    } else {

        while (true) {

            if (lines[srcLineNr] == NULL) {
                return NULL;
            }

            if (i >= strSz - 1) {
                strSz *= 2;
                tokenStr = (char *) realloc(tokenStr, sizeof(char) * strSz);
            }

            if (strchr(DELIMITERS, lines[srcLineNr][colPos])) {

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

    }

    tokenStr[i] = '\0';

    if (!advance) {
        srcLineNr = savedLineNr;
        colPos = savedColPos;
    }

    //printf("returning: %s\n", tokenStr);
    return tokenStr;

}

char resolveEscapeSequence(char escapedChar) {
    switch (escapedChar) {
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case '\\':
            return '\\';
        case '"':
            return '"';
        case '\'':
            return '\'';
        case '`':
            return '`';
        default:
            internalError("Attempted to resolve an invalid escape character");
    }
}

/*
Advances the scanner's internal cursor by one character
*/
void advanceCursor() {

    colPos++;

    if (colPos >= strlen(lines[srcLineNr])) {
        // We've reached the end of this line
        srcLineNr++;
        colPos = 0;
    }

    //printf("advanced to line %d, %d\n", srcLineNr, colPos);

}
