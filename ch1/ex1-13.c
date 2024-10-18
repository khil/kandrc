#include <stdio.h>

/*
 * Exercise 1-12.  Write a program that prints a histogram of the lengths of words in
 * its input.  Its easy to draw a histogram with bars horizontal; a vertical
 * orientation is more challenging.
*/

#define IN 1
#define OUT 2
#define MAX_WORD_LENGTH 26

int main() {
	int c, i, state, start_i;
	int word_len[MAX_WORD_LENGTH];
	state = OUT;

	/* init the array to zero */
	for(i = 0; i < MAX_WORD_LENGTH; i++) {
		word_len[i] = 0;
	}

	/* count the words in the input stream */
	for (i = 0; (c = getchar()) != EOF; i++) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN) {
				state = OUT;
				word_len[i - start_i]++;
			}
		}
		else {
			if (state == OUT) {
				state = IN;
				start_i = i;
			}
		}
	}

	/* write the results to the stdout */
	for(i = 1; i < MAX_WORD_LENGTH; i++) {
		printf("%2d> ", i);
		for (start_i = 0; start_i < word_len[i]; start_i++) {
			putchar('|');
		}
		putchar('\n');
	}
}
