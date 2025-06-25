#include <stdio.h>
#include "../str.h"
#include <string.h>

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

const char *any(const char *s1, const char *s2) {
    const char *s;
    char *i = NULL;

    for (const char *t = s2; *t; t++) {
        for (s = s1; *s; s++) {
            if (*s == *t) {
                printf("t = %c = %ld\n", *t, t - s1);
                if (i != NULL) {
                    printf("i = %i = %ld\n", *i, i - s1);
                    i = (char *) t;
                }

            }

                //if (i == NULL || (s1 - t) < (s1 - i))
                //    i = (char *) t;
        }
    }

    return i;
}


int main() {
	char line[MAXLEN];
	int32_t len;

	while ((len = _getline(line, MAXLEN)) > 1) {
		const char *res = any(line, "aeiou");
		printf("location of a, e, i, o, or u: %ld\n", res - line);
        char *r = strpbrk(line, "aeiou");
		printf("location of a, e, i, o, or u: %ld\n", r - line);
	}
	return 0;
}



