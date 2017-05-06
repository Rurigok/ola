#include "scanner.h"
#include "parser.h"

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
