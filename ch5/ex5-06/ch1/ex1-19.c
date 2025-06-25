#include <stdio.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 1-19. Write a function "reverse(s)" that reverses the
 * character string s. Use it to write a program that reverses its input a line
 * a time.
*/

#define MAXLINE 1000

int32_t main() {
	int32_t len;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) != EOF) {
		if (len > 0) {
			reverse(line);
			printf("%s", line);
		}
	}

	return 0;
}

