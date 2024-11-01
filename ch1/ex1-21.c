#include <stdio.h>

/*
 * Exercise 1-21. Write a program "entab" that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the
 * same tab stops as for the "detab". When either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
*/

#define MAXLINE 1000
#define TAB_WIDTH 8


int _getline(char line[], int maxline);
int entab(char str[], int len);


int main() {
	int len, o_len;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) != EOF) {
		printf("before-%3d: %s", len, line);
		o_len = len;
		if (len > 0)
			len = entab(line, len);

		printf(" after-%3d: %s\t%d tabs added!\n", len, line, (o_len - len) / (TAB_WIDTH - 1));
	}

	return 0;
}


int entab(char str[], int len) {
	int i, j, blank;

	for (i = 0; i < len - 1; i++) {
		if (str[i] == ' ') {
			if (blank != 0) {
				if ((i - blank) == (TAB_WIDTH - 1)) {
					str[blank] = '\t';
					// shift everything TAB_WIDTH - 1 to the left
					for (j = blank + TAB_WIDTH; j <= len; j++)
						str[j - (TAB_WIDTH - 1)] = str[j];
					len = len - (TAB_WIDTH - 1);
					i = blank;
					blank = 0;
				}
			}
			else
				blank = i;
		}
		else
			blank = 0;
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

