#include <stdio.h>

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 1-16, getline and putline functions using pointers
 */

#define MAXLINE 1000

int _getline(char *line, int maxline) {
    int c, i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++, line++)
        *line = c;

    if (c == '\n') {
        *line++ = c;
        i++;
    }
    *line = '\0';

    return i;
}

int _putline(char *line, int len) {
    int i;

	for (i = 0; i <= len && *line; line++, i++)
		putchar(*line);

    return i;
}


int main() {

    int len, i;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) > 0) {
		printf("len=%03d: ", len);
		_putline(line, len);
	}

    return 0;
}
