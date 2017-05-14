#ifndef OLA_PARSER_H
#define OLA_PARSER_H

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
void parseStatement(bool exec);
void parseDeclaration(bool exec);
value_t *parseExpression(bool exec, char *terminatingStr, bool toEOL);
value_t *resolveLiteral(token_t *token);

#endif
