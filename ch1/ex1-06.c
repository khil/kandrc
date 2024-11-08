#include <stdio.h>

/*
 * Exercise 1-6.  Verify that the expression getchar() != EOF is 0 or 1.
*/

int main() {
	printf("Press any key then press ENTER.  Use Ctrl-D to input EOF.\n");
	printf("Result ==>  %d\n", (getchar() != EOF));
}
