#include <stdio.h>

/*
 * Exercise 1-10.  Write a program to copy its input to its output, replacing each
 * tab by \t, each backspace by \b, and each backslash by \\.  This makes tabs
 * and backspaces visible in an unambiguous way.
*/

int main() {
	int c;

	while((c = getchar()) != EOF) {
		if (c == '\t') {
			printf("\\t");
			c = 0;
		}
		if (c == '\b') {
			printf("\\b");
			c = 0;
		}
		if (c == '\\') {
			printf("\\\\");
			c = 0;
		}
		
		if (c != 0)
			putchar(c);
	}
}
