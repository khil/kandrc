#include <stdio.h>

/*
 * Exercise 1-19. Write a function "reverse(s)" that reverses the character
 * string s. Use it to write a program that reverses its input a line a time.
*/

#define MAXLINE 1000
#define TRUE 1
#define FALSE 0

int _getline(char line[], int maxline);
void reverse(char s[], int len, short perserve_nl);


int main() {
	int len;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) != EOF) {
		if (len > 0) {
			reverse(line, len, TRUE);
			printf("%s", line);
		}
	}

	return 0;
}


void reverse(char s[], int len, short perserve_nl) {
	int i;
	char c;

	if (perserve_nl == TRUE && (s[len] == '\n'))
		len--;

	for (i = 0; i <= (--len / 2); i++) {
		c = s[i];
		s[i] = s[len - i];
		s[len - i] = c;
	}
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
	else if (c == EOF)
		return EOF;
	else
		return 0;
}

