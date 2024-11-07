#include <stdio.h>

/*
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input/ Make sure your program  does something intelligent with very
 *  long lines, and if there are no blanks to tabs before the specific column.
*/

#define MAXLINE 1000
#define WRAP_COLUMN 40


int _getline(char line[], int maxline);


int main() {
	int len, fold_at, i, add_hyphen, last_i;
	char line[MAXLINE];

	// print a column heading
	for (int i = 1; i <= WRAP_COLUMN; i++)
		printf("%d", (i / 10) % 10);
	putchar('\n');
	for (int i = 1; i <= WRAP_COLUMN; i++)
		printf("%d", i % 10);
	putchar('\n');


	while ((len = _getline(line, MAXLINE)) > 0) {
		if (len > WRAP_COLUMN) {
			last_i = 0;

			while (last_i < len) {
				fold_at = 0;
				add_hyphen = 0;
				for (i = last_i + WRAP_COLUMN; i > last_i; i--) {
					if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
						fold_at = i;
						i = -1;
					}
				}

				if (fold_at == 0) {
					add_hyphen = 1;
					fold_at = last_i + (WRAP_COLUMN - 1);
				}

				for (i = last_i; i < fold_at; i++)
					putchar(line[i]);

				if (add_hyphen == 1)
					putchar('-');

				putchar('\n');
				if (add_hyphen == 1)
					last_i = fold_at;
				else
					last_i = fold_at + 1;
			}
		}
		else
			printf("%s", line);
	}

	return 0;
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

