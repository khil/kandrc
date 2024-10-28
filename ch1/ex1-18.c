#include <stdio.h>

/*
 * Exercise 1-18. Write a program to remove training blanks and tabs from each
 * line of input, and delete entirely blank lines.
*/

#define MAXLINE 1000

int _getline(char line[], int maxline);

int main() {
	int len;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) != EOF) {
		if (len > 0)
			printf("%03d  %s", len, line);
	}

	return 0;
}


int _getline(char line[], int maxline) {
	int c, i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;

	if (i > 0) {
		for (; line[i-1] == ' ' || line[i-1] == '\t'; i--)
			;

		if (c == '\n')
			line[i++] = c;
		line[i] = '\0';

		return i;
	}
	else {
		if (c == EOF)
			return EOF;
		else
			return 0;
	}
}

