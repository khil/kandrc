#include <assert.h>
#include <limits.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 3-6. write a version of itoa that accepts three arguments
 * instead of two.  The third argument is a minimum field width; the converted
 * number must be padded with blanks on the left if necessary to make it wide
 * enough.
 */

#define BUF_SIZE 1000


int32_t _abs(int32_t v) {
    /* simple absolute value function */
    return v < 0 ? -v : v;
}


char *itoa(int n, char *s) {
    int32_t sign = n;
    char *res = s;

    do {
        *s++ = _abs(n % 10) + '0';
    } while((n /= 10) != 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(res);
    return res;
}


int32_t main() {
    char s[BUF_SIZE];

    /* 65535 : _s & s = "          65535" (pass) */
    uint16_t ushort_max = ~0;
    itoa(ushort_max, s);
    assert(_strcmp(s, "65535") == 0);

    /* -32768 : _s & s = "         -32768" (pass) */
    int16_t short_min = (short) (1 << ((sizeof(short) * CHAR_BIT) - 1));
    itoa(short_min, s);
    assert(_strcmp(s, "-32768") == 0);

    /* 2147483647 : _s & s = "2147483647"  */
    int32_t int_max = ~(1 << ((sizeof(int) * CHAR_BIT) - 1));
    itoa(int_max, s);
    assert(_strcmp(s, "2147483647") == 0);

    /* -2147483648 :  s != "-2147483648"  */
    int32_t int_min = (1 << ((sizeof(int) *  CHAR_BIT) - 1));
    itoa(int_min, s);
    assert(_strcmp(s, "-2147483648") == 0);
    
    return 0;
}
