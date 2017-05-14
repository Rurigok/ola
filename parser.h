#ifndef OLA_PARSER_H
#define OLA_PARSER_H

#include <stdbool.h>

#include "scanner.h"

typedef enum dataType_t {
    DT_INTEGER,
    DT_FLOAT,
    DT_STRING,
    DT_BOOLEAN,
    DT_OBJECT,
    DT_FUNCTION
} dataType_t;

typedef struct value_t {
    dataType_t dataType;
    char *value;
} value_t;

void beginParsing();
value_t callFunction(bool exec, int args, ...);
void parseClass(bool exec);
void parseDeclaration(bool exec);
void parseDef(bool exec);
value_t *parseExpression(bool exec, char *terminatingStr, bool toEOL);
void parseFor(bool exec);
void parseIf(bool exec);
void parseStatement(bool exec);
void parseWhile(bool exec);

int comparePrecedence(token_t *onStack, token_t *current);
value_t *resolveLiteral(token_t *token);

#endif //OLA_PARSER_H
