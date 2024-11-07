#include <stdio.h>

/*
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input/ Make sure your program  does something intelligent with very
 * long lines, and if there are no blanks to tabs before the specific column.
*/

#define MAXLINE 1000
#define WRAP_COLUMN 30
#define TAB_WIDTH 8
#define ERROR -2


int _getline(char line[], int maxline);
int detab(char str[], int len, int max_len);
void fold(char str[], int len);


int main() {
	int len, fold_at, i, add_hyphen, last_i;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) > 0) { 
		/* swap the tabs for spaces to ensure proper width/folding */
		if (len > 0)
			len = detab(line, len, MAXLINE);

		if (len == ERROR)
			printf("ERROR: insufficient array space!");
		else if (len > WRAP_COLUMN)
			fold(line, len);
		else
			printf("%s", line);
	}

	return 0;
}


void fold(char str[], int len) {
	int fold_at, i, add_hyphen, last_i = 0;

	while (last_i < len) {
		fold_at = 0;
		add_hyphen = 0;
		for (i = last_i + WRAP_COLUMN; i > last_i; i--) {
			if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
				fold_at = i;
				i = -1;
			}
		}

		if (fold_at == 0) {
			add_hyphen = 1;
			fold_at = last_i + (WRAP_COLUMN - 1);
		}

		for (i = last_i; i < fold_at; i++)
			putchar(str[i]);

		if (add_hyphen == 1)
			putchar('-');

		putchar('\n');
		if (add_hyphen == 1)
			last_i = fold_at;
		else
			last_i = fold_at + 1;
	}
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

	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}

