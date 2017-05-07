#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "scanner.h"
#include "parser.h"
#include "error.h"

extern token currentToken;

void beginParsing() {

    // Call parseStatement until the end of the file
    while (currentToken.primClass != TOK_EOF) {
        parseStatement(true);
    }

}

void parseStatement(bool exec) {

}

void parseExpression(bool exec) {

}
