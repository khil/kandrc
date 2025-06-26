#include <stdio.h>
#include <stdint.h>

#if !defined(__STR_H__)
#define __STR_H__
int32_t _getline(char *line, int32_t maxlen);
int32_t _putline(char *line);
size_t _strlen(char *s);
int32_t _strcmp(const char *s, const char *t);
char *reverse(char *s);
#endif

