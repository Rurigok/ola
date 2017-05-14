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
        // Non-array type was declared

        getNext();

        value_t *value = parseExpression(exec, NULL, true);

    } else {

    }

}

void parseAssignment(bool exec) {

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

    // Postfix expression is populated

    // TODO: Evaluate postfix expression

    return NULL;

}

int comparePrecedence(char *onStack, char *current) {

    // TODO: return 1 if current operator has a higher pred than onStack, 0 if equal, -1 otherwise

    return 0;

}

value_t *resolveLiteral(token_t *token) {

    if (token->primClass != OPERAND) {
        internalError("Attempted to resolve value of non-literal");
    }

    value_t *value = (value_t *) calloc(sizeof(value_t), 1);

    if (value == NULL)
        sysError("malloc value");

    value->value = token->tokenStr;
    value->dataType = token->subClass;

    return value;

}
