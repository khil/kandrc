#include <stdio.h>

/*
 * Exercise 1-8.  Write a program to count blanks,tabs, and newlines.
*/

int main() {
	int blanks, tabs, newlines, c;
	blanks = 0;
	tabs = 0;
	newlines = 0;

	while((c = getchar()) != EOF) {
		if (c == ' ')
			++blanks;
		if (c == '\t')
			++tabs;
		if (c == '\n')
			++newlines;
	}

	printf("blanks: %d\ntabs: %d\nnewlines: %d\n", blanks, tabs, newlines);
}
