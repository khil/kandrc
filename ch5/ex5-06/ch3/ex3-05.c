#include <assert.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 3-5. Write a function itob(n,s,b) that converts the
 * integer n into a base b character representation in the string s.  In
 * particular, itob(n,s,16) formates n as a hexadecimal integer in s.
 */

#define BUF_SIZE 100
#define BASE_CHARS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ERROR_MSG "ERROR: Invalid Base Specified!"



int32_t _abs(int32_t v) {
    /* simple absolute value function */
    return v < 0 ? -v : v;
}


char *itob(int32_t n, char *s, const uint8_t b) {
    /* handles conversions up to base-36 */
    char *p = s;
    if (b > 1 && b <= _strlen(BASE_CHARS)) {
        int32_t sign = n;

        do {
            *p++ = BASE_CHARS[_abs(n % b)];
        } while((n /= b) != 0);
        if (sign < 0)
            *p++ = '-';
        *p = 0;
        reverse(s);
    }
    else
        _strcpy(p, ERROR_MSG);

    return s;
}


int32_t main() {
    char s[BUF_SIZE];

    itob(143, s, 46);
    assert(_strcmp(s, ERROR_MSG) == 0);

    itob(143, s, 36);
    assert(_strcmp(s, "3Z") == 0);

    itob(143, s, 16);
    assert(_strcmp(s, "8F") == 0);

    itob(143, s, 8);
    assert(_strcmp(s, "217") == 0);

    itob(143, s, 2);
    assert(_strcmp(s, "10001111") == 0);

    itob(-143, s, 8);
    assert(_strcmp(s, "-217") == 0);

    itob(0256, s, 8);
    assert(_strcmp(s, "256") == 0);

    itob(0b11111111, s, 16);
    assert(_strcmp(s, "FF") == 0);

    itob(0xFF, s, 2);
    assert(_strcmp(s, "11111111") == 0);

    itob(0xFFFF, s, 2);
    assert(_strcmp(s, "1111111111111111") == 0);

    return 0;
}
