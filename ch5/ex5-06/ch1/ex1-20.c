#include <stdio.h>
#include <stdint.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * rewrite of exercise 1-20. Write a program "detab" that replaces tabs in the
 * input with the proper number of blanks to space to the next tab stop.
 * Assume a fixed set of tab stops, every n columns.  Should n be a variable or
 * a symbolic parameter?
*/

#define MAXLINE 1000
#define TAB_WIDTH 8
#define ERROR -2


int32_t detab(char *str, int32_t len, int32_t max_len) {
    /* replace tabs with N number of spaces */
    char *s, *e;

    for (s = str; *s; s++) {
		if (*s == '\t') {
			if (len + (TAB_WIDTH - 1) <= max_len) {
				/* shift the rest of the array N chars to the right */
                for (e = str + len; e != s; e--)
                    *(e + (TAB_WIDTH - 1)) = *e;
				/* fill the new space with spaces */
                while (e != s + TAB_WIDTH)
                    *e++ = ' ';
				/* increase the length of the string */
				len = len + (TAB_WIDTH - 1);
            }
			else
				return ERROR;
        }
    }

	return len;
}


int32_t main() {
	int32_t len;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) > 0) {
		if (len > 0) {
            printf("before: %d -> %s", len, line);
			len = detab(line, len, MAXLINE);
            printf("after : %d -> %s", len, line);
        }
        else if (len == ERROR)
			printf("ERROR: insufficient array space!");
	}

	return 0;
}

