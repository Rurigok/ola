#ifndef OLA_SCANNER_H
#define OLA_SCANNER_H

#include <stdio.h>
#include <stdbool.h>

#define LINE_BUFFER_DEFAULT 160
#define NUM_LINES_DEFAULT 100
#define TOKEN_DEFAULT_LEN 20

#define DELIMITERS "!@#%^&*()-+=[]/<>,~;:\"' \t\n\r\v"
#define WHITESPACE " \v\t\n\r"
#define QUOTES "\"'`"
#define ESCAPABLE "\\\"'ntr`"

#define IDENTIFIER_ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

// Primary classifications
typedef enum primClass_t {
    DATA_TYPE,
    OPERAND,
    OPERATOR,
    TOK_EOF
} primClass_t;

// Secondary classifications
typedef enum subClass_t {
    IDENTIFIER,
    STRING,
    INTEGER,
    FLOAT,
    BOOL,
    FOR,
    WHILE,
    IF,
    ELSE,
    DEF,
    IN,
    SELECT,
    WHEN,
    CLASS,
    NNET,
    LIST,
    MATRIX
} subClass_t;

typedef struct token_t {
    char *tokenStr;
    primClass_t primClass;
    subClass_t subClass;
} token_t;

void initScanner(FILE *file);
void testScanner();

char * getNext();
char resolveEscapeSequence(char escapedChar);
void classifyToken(token_t *tok);
char * readNextToken(bool advance);
void advanceCursor();

#endif
