#include <stdio.h>

/*
 * Exercise 1-9.  Write a program to copy its input to its output, replacing each
 * string of one or more blanks by a single blank.
*/

int main() {
	int c, blanks;

	for(blanks = 0; (c = getchar()) != EOF; ) {
		if (c == ' ')
			++blanks;
		if (c != ' ')
			blanks = 0;
		if (blanks <= 1)
			printf("%c", c);
	}
}
