#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_DEFAULT 160
#define NUM_LINES_DEFAULT 100
#define TOKEN_DEFAULT_LEN 20

#define DELIMITERS "!@#%^&*()-+=[]/<>,~;:\"' \t\n\r\v"
#define WHITESPACE " \v\t\n\r"

// Primary classifications
typedef enum primClass_t {
    OPERAND,
    OPERATOR,
} primClass_t;

// Secondary classifications
typedef enum subClass_t {
    IDENTIFIER
} subClass_t;

typedef struct token {
    char *tokenStr;
    primClass_t primClass;
    subClass_t subClass;
} token;

void initScanner(FILE *file);
void testScanner();

char * getNext();
void classifyToken(token *tok);
char * readNextToken(bool advance);
void advanceCursor();
