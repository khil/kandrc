#include <stdio.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 1-21. Write a program "entab" that replaces strings of
 * blanks by the minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for the "detab". When either a tab or a single
 * blank would suffice to reach a tab stop, which should be given preference?
*/

#define MAXLINE 1000
#define TAB_WIDTH 8


int32_t entab(char *str) {
    /* replace N spaces with tabs */
    char *b, *p, *s;

    for (s = str; *s; s++) {
        if (*s == ' ') {
            if (b != NULL) {
                if ((s - b) + 1 == TAB_WIDTH) {
					// insert the tab and shift everything starting at s, TAB_WIDTH - 1 to the left
                    *b++ = '\t';
                    s++;
                    for (p = b; *s; p++, s++)
                        *p = *s;
                    *p = 0;
                    s = b;
                    b = NULL;
                }
            }
            else
                b = s;
        }
        else
            b = NULL;
    }

	return s - str;
}


int32_t main() {
	int32_t len, o_len;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) != EOF) {
		printf("before-%3d: %s\n", len, line);
		o_len = len;
		if (len > 0)
			len = entab(line);

		printf(" after-%3d: %s\t%d tabs added!\n", len, line, (o_len - len) / (TAB_WIDTH - 1));
	}

	return 0;
}

