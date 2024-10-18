#include <stdio.h>

/*
 * Exercise 1-14.  Write a program to print a histogram of the frequencies of dif-
 * ferent characters in its input.
*/

#define MAX_CHARS 129

int main() {
	int c, i, j;
	int chars[MAX_CHARS];

	/* init the array to zero */
	for(i = 0; i < MAX_CHARS; i++) {
		chars[i] = 0;
	}

	/* count the various characters in the input stream */
	for (i = 0; (c = getchar()) != EOF; i++) {
		if (c < MAX_CHARS)
			chars[c]++;
		else
			chars[MAX_CHARS - 1]++;  /* handle extended char codes & Unicode in one bucket */
	}

	/* write the results to the stdout displaying only the chars that were input */
	for(i = 0; i < MAX_CHARS; i++) {
		if (chars[i] > 0) {
			printf("0x%02x ", i);
			if (i <= 0x20 || i > 0x7F) {
				/* handle non-displayable characters */
				if (i == '\t')
					printf("(\\t)");
				else if (i == '\r')
					printf("(\\r)");
				else if (i == '\n')
					printf("(\\n)");
				else if (i == ' ')
					printf("(SP)");
				else
					printf("(--)");
			}
			else
				printf("(%c) ", i);

			printf(" > ");
			for (j = 0; j < chars[i]; j++)
				putchar('|');
			putchar('\n');
		}
	}
}
