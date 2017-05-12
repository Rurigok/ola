#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "scanner.h"
#include "parser.h"
#include "error.h"

extern token_t currentToken;
extern token_t nextToken;

void beginParsing() {

    // Call parseStatement until the end of the file
    while (currentToken.primClass != TOK_EOF) {
        parseStatement(true);
    }

}

void parseStatement(bool exec) {

    if (currentToken.primClass == DATA_TYPE) {
        parseDeclaration(exec);
    } else if (currentToken.primClass == OPERAND) {
        if (currentToken.subClass == IDENTIFIER) {
            parseAssignment(exec);
        }
    }

}

void parseDeclaration(bool exec) {

    char *dataType = strdup(currentToken.tokenStr);

    if (dataType == NULL) {
        sysError("strdup");
    }

    getNext();

    char *identifier = strdup(currentToken.tokenStr);

    getNext();

    if (currentToken.tokenStr[0] == '[') {
        // Array
    } else if (currentToken.tokenStr[0] == '=') {
        // Non-array
    } else {

    }

}

void parseAssignment(bool exec) {

}

void parseExpression(bool exec) {

}
