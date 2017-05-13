#ifndef OLA_ERROR_H
#define OLA_ERROR_H

void internalError(const char *message);    // Internal interpreter error
void sysError(const char *message);         // External syscall error

void syntaxError(const char *message, int srcLineNr);

#endif