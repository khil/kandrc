#include <stdio.h>

/*
 * Exercise 1-2.  Experiment to find out what happens when printf's argument
 * string contains \c where c is some character not listed above.
 *
 * this code will not compile!
*/
int main() {
	printf("Hello, world!\q\n");
	return 0;
}

