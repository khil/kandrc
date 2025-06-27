#include <stdio.h>
#include "str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 1-16. _getline and _putline functions used in multiple
 * exercises.
 */

size_t _strlen(char *s) {
    size_t i = 0;
    
    for (; *s; s++, i++)
        ;

    return i;
}


int32_t _strcmp(const char *s, const char *t) {
    /* A quick & dirty implementation of strcmp (string compare) :
     * returns 0 when s & t are identical otherwise 1.
     */
    for (; *s == *t; s++, t++)
        if (*s == 0)
            return 0;

    return *s - *t;
}


char *_strcpy(char *s, const char *t) {
    /* A quick & dirty implementation of strcpy (string copy).
     * The number of characters copied is returned
     */

    char *d = s;

    for(char *p = (char *) t; *p; p++, d++)
        *d = *p;

    return d;
}


char *reverse(char *s) {
    if (s) {
        char *str = s;
        char *end = s + _strlen(s) - 1;
        char tmp;

        for (; str < end; str++, end--) {
            tmp = *str;
            *str = *end;
            *end = tmp;
        }
    }

    return s;
}


int32_t _getline(char *line, int32_t maxlen) {
	int32_t c;
    char *s = line;

	while ((line - s) < (maxlen - 1) && (c = getchar()) != EOF && c != '\n')
		*s++ = c;

    if (c == EOF)
        return EOF;

    if (c == '\n')
		*s++ = c;
	*s = '\0';

    return s - line;
}


int32_t _putline(char *line) {
    char *s = line;
    while (*s != 0)
		putchar(*s++);
    return s - line;
}

