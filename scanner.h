#define LINE_BUFFER_DEFAULT 160
#define NUM_LINES_DEFAULT 100

#define DELIMITERS "!@#%^&*()-+=[]/<>,~;:\"'"
#define WHITESPACE " \v\t\n\r"

typedef struct token {
    char *tokenStr;
    int primClass;
    int subClass;
} token;

void initScanner(FILE *file);
char * getNext();
