#include <stdio.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 2-4. Write an alternate version of sqeeze(s1, s2) that
 * deletes each character is s2 that matches any character in the string s2.
*/

#define MAXLEN 1000


int32_t squeeze(char *s1, const char *s2) {
    char *s, *u;
    const char *t;
    
    for (t = s2; *t; t++) {
        for (s = s1; *s; s++) {
			if (*s == *t) {
				for (u = s; *u; u++) {
                    *u = *(u + 1);
                }
                *u = '\0';
            }
        }
    }

    return s - s1;
}


int32_t main() {
	char line[MAXLEN];
	int32_t len;

	while ((len = _getline(line, MAXLEN)) > 1) {
		printf("before: %d --> %s", len, line);
		len = squeeze(line, "abc");
		printf("after: %d --> %s", len, line);
	}

	return 0;
}


