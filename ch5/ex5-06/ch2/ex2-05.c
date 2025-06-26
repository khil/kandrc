#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 2-5. Write an function any(s1, s2), which returns the
 * first location in the string s1 where any character from the string s2
 * occurs, or -1 if s1 contains no characters from s2. (The standard library
 * function strpbrk does the same job but returns a pointer to the
 * location.)
*/

#define MAXLEN 1000


char *any(const char *s1, const char *s2) {
    char *r = NULL;
    char *p;
 
    for (char *q = (char *) s2; *q; q++) {
        for (p = (char *) s1; *p; p++) {
            if (*q == *p) {
                if (!r || p - s1 < r - s1)
                    r = p;
            }
        }
    }
 
    return r;
}


int main() {
	char line[MAXLEN];
	int32_t len;

	while ((len = _getline(line, MAXLEN)) > 1) {
		char *p = any(line, "aeiou");
        char *q = strpbrk(line, "aeiou");

        assert(*p == *q);
        assert(p - line == q - line);
	}
	return 0;
}



