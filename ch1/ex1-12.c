#include <stdio.h>

/*
 * Exercise 1-12.  Write a program that prints its input one work per line
*/

#define IN 1
#define OUT 2

int main() {
	int c, state;

	state = OUT;

	while((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN) {
				putchar('\n');
				state = OUT;
			}
		}
		else {
			state = IN;
			putchar(c);
		}
	}
}
