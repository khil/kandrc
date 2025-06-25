#include <stdio.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 1-16. Revise the main routine of the longest-line program
 * so it will correctly print the length of arbitrarily long input lines, and as
 * much as possible or the text.
 */

#define MAXLINE 1000

int32_t main() {
	int32_t len;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) > 0) {
		printf("len=%03d: ", len);
		_putline(line);
	}

	return 0;
}

