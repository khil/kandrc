#include <stdio.h>

/*
 * Exercise 1-13.  Write a program to print a histogram of the lengths of words in
 * its input.  Its easy to draw a histogram with bars horizontal; a vertical
 * orientation is more challenging.
*/

#define IN 1
#define OUT 2
#define MAX_WORD_LEN 10

int main() {
	int c, i, state, strt_i, len;
	int word_len[MAX_WORD_LEN + 1];
	state = OUT;

	/* init the array to zero */
	for(i = 0; i < MAX_WORD_LEN + 1; i++)
		word_len[i] = 0;

	/* count the words in the input stream */
	for (i = 0; (c = getchar()) != EOF; i++) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN) {
				state = OUT;
				len = (i - strt_i) - 1;
				if (len < MAX_WORD_LEN)
					word_len[len]++;
				else
					word_len[MAX_WORD_LEN]++;
			}
		}
		else {
			if (state == OUT) {
				state = IN;
				strt_i = i;
			}
		}
	}

	/* write the results to the stdout */
	for(i = 0; i < MAX_WORD_LEN + 1; i++) {
		if (i < MAX_WORD_LEN)
			printf("%3d> ", i + 1);
		else
			printf("%d+> ", MAX_WORD_LEN);
		for (strt_i = 0; strt_i < word_len[i]; strt_i++)
			putchar('|');
		putchar('\n');
	}
}
