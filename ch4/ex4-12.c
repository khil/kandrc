#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Exercise 4-12.  Adapt the idea of printd to write a recursive version of itoa;
 * that is, convert and integer into a string by calling a recursive routine.
 */

void itoa(int n, char s[]) {
    static int i = 0;

    if (n / 10)
        itoa(n / 10, s);
    else {
        i = 0;
        if (n < 0)
            s[i++] = '-';
    }
     
    s[i++] = abs(n % 10) + '0';
    s[i] = 0;
}

int main() {
    char s[100];

    itoa(-1234, s);
    assert(strcmp(s, "-1234") == 0);

    itoa(43210, s);
    assert(strcmp(s, "43210") == 0);

    itoa(8675309, s);
    assert(strcmp(s, "8675309") == 0);

    return 0;
}
