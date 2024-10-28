#include <stdio.h>

/*
 * Exercise 1-16. Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrarily long input lines, and as much as possible
 * or the text.
*/

#define MAXLINE 1000

int _getline(char line[], int maxline);
int _putline(char line[], int len);


int main() {
	int len, i;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) > 0) {
		printf("len=%03d: ", len);
		_putline(line, len);
	}

	return 0;
}


int _getline(char line[], int maxline) {
	int c, i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;

	if (c == '\n') {
		line[i] = c;
		i++;
	}

	line[i] = '\0';

	return i;
}


int _putline(char line[], int len) {
	int i;
	
	for (i = 0; i <= len && line[i] != '\0'; i++) {
		putchar(line[i]);
	}

	return i;
}
