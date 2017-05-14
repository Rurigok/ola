#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "deque.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"

extern token_t currentToken;
extern token_t nextToken;
extern int srcLineNr;

void beginParsing() {

    // Call parseStatement until the end of the file
    while (currentToken.primClass != TOK_EOF) {
        parseStatement(true);
    }

}

void parseStatement(bool exec) {

    if (currentToken.primClass == DATA_TYPE) {
        parseDeclaration(exec);
    } else if (currentToken.subClass == IDENTIFIER) {
        parseAssignment(exec);
    } else if (currentToken.subClass == DEF) {
        parseDef(exec);
    } else if (currentToken.subClass == CLASS) {
        parseClass(exec);
    } else if (currentToken.subClass == IF) {
        parseIf(exec);
    } else if (currentToken.subClass == FOR) {
        parseFor(exec);
    } else if (currentToken.subClass == WHILE) {
        parseWhile(exec);
    } else if (currentToken.primClass == FUNCTION) {
        parseExpression(exec, NULL, true);
    }

}

void parseAssignment(bool exec) {

}

void parseClass(bool exec) {

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
        // Non-array type was declared

        getNext();

        value_t *value = parseExpression(exec, NULL, true);

    } else {

    }

}

void parseDef(bool exec) {

}

/*
 * parseExpression is called on
 */
value_t *parseExpression(bool exec, char *terminatingStr, bool toEOL) {

    deque *postfixStack = createDeque();
    deque *operatorStack = createDeque();

    int startLineNr = srcLineNr;

    for (;;) {

        if (strcmp(currentToken.tokenStr, terminatingStr) || ((srcLineNr != startLineNr) && toEOL)) {
            break;
        }

        token_t *current = dupToken(&currentToken);

        if (current->primClass == OPERAND) {
            // Append all operands to output

            dequePush(postfixStack, current);

        } else if (current->subClass == R_PAREN) {
            // Pop each operator and append to output until we find left paren in operator stack

            //dequePush(operatorStack, current);

        } else if (current->primClass == OPERATOR) {
            // Pop from operator stack and append to output until we find an operator with a lower precedence than
            // the current token, then push current to stack.

            if (operatorStack->size == 0) {

                dequePush(operatorStack, current);

            } else {

                token_t *topOperator = dequePeek(operatorStack);
                token_t *poppedOperator;

                int pred = comparePrecedence(topOperator->tokenStr, current->tokenStr);

                while (operatorStack->size > 0 && pred >= 0) {
                    poppedOperator = dequePop(operatorStack);
                    dequePush(postfixStack, poppedOperator);
                    topOperator = dequePeek(operatorStack);
                    pred = comparePrecedence(topOperator->tokenStr, current->tokenStr);
                }

                dequePush(operatorStack, current);

            }

        } else {
            syntaxError("Unexpected symbol found in expression", startLineNr);
        }

        getNext();

    }

    while (operatorStack->size > 0) {
        dequePush(postfixStack, dequePop(operatorStack));
    }

    // Postfix expression is populated

    // TODO: Evaluate postfix expression

    return NULL;

}

void parseFor(bool exec) {

}

void parseIf(bool exec) {

}

void parseWhile(bool exec) {

}

value_t callFunction(bool exec, int args, ...) {

}

int comparePrecedence(token_t *onStack, token_t *current) {

    if (current->precedence > onStack->precedence) {
        return 1;
    } else if (current->precedence == onStack->precedence) {
        return 0;
    } else {
        return -1;
    }

}

value_t *resolveLiteral(token_t *token) {

    if (token->primClass != OPERAND) {
        internalError("Attempted to resolve value of non-literal");
    }

    value_t *value = (value_t *) calloc(sizeof(value_t), 1);

    if (value == NULL)
        sysError("malloc value");

    value->value = token->tokenStr;

    switch (token->subClass) {
        case INTEGER:
            value->dataType = DT_INTEGER;
            break;
        case FLOAT:
            value->dataType = DT_FLOAT;
            break;
        case BOOLEAN:
            value->dataType = DT_BOOLEAN;
            break;
        case STRING:
            value->dataType = DT_STRING;
            break;
    }

    return value;

}
