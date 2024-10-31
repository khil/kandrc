#include <stdio.h>

/*
 * Exercise 1-20. Write a program "detab" that replaces tabs in the input with the
 * proper number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, every n columns.  Should n be a variable or a symbolic parameter?
*/

#define MAXLINE 1000
#define TAB_WIDTH 8
#define ERROR -2

int _getline(char line[], int maxline);
int detab(char str[], int len, int max_len);


int main() {
	int len, o_len;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) != EOF) {
		printf("before-%3d: %s", len, line);
		o_len = len;
		if (len > 0)
			len = detab(line, len, MAXLINE);

		if (len == ERROR)
			printf("ERROR: insufficient array space!");
		else {
			printf(" after-%3d: %s\t%d tabs replaced!\n", len, line, (len - o_len) / (TAB_WIDTH - 1));

		}
	}

	return 0;
}

int detab(char str[], int len, int max_len) {
	int i, j;
	for (i = 0; i < len; i++) {
		if (str[i] == '\t') {
			if (len + (TAB_WIDTH - 1) <= max_len) {
				/* shift the rest of the array N chars to the right */
				for (j = len; j > i; j--)
					str[j + (TAB_WIDTH - 1)] = str[j];
				/* fill the new space with spaces */
				for (j = i + TAB_WIDTH; i < j; i++)
					str[i] = ' ';
				/* increase the length of the string */
				len = len + (TAB_WIDTH - 1);
				/* decrement i, otherwise it will skip a char when the main loop increments it */
				i--;
			}
			else
				return ERROR;
		}
	}

	return len;
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

