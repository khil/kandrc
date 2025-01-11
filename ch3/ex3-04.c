#include <assert.h>
#include <limits.h>

/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n equal
 * to -(2^wordsize-1). Explain why not. Modify it to print the value correctly
 * regardless of the machine on which it runs.
 */

#define BUF_SIZE 100

void reverse(char s[]) {
    /* reverse string */
	int len, c;

    for(len=0; s[len] != 0; ++len);
    len--;

    for(int i=0; i <= (len / 2); i++) {
		c = s[i];
		s[i] = s[len - i];
		s[len - i] = c;
    }
}

int _abs(int v) {
    /* simple absolute value function */
    return v < 0 ? -v : v;
}

void _itoa(int n, char s[]) {
    /*
     * This version correctly handles the largest negative number.
     *
     * The reason the original fails on the largest negative number is two fold:
     *    1. The 'n = -n;' flips the sign, but the resulting number +2147483648,
     *       overflows the integer by 1, resulting in the same number we started
     *       with.
     *    3. Then n being left negative is not properly handled in the do-while
     *       loop, so negative values generated in the division and modulo op-
     *       erations cause garbage being added to the string and the loop
     *       ending early before being finished.
     */
    int i = 0, sign = n;

    do {
        s[i++] = _abs(n % 10) + '0';
    } while((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


void itoa(int n, char s[]) {
    /* book version of itoa */
    int i, sign;

    if((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


int str_cmp(const char s[], const char t[]) {
    /* A quick & dirty implementation of strcmp (string compare) :
     * returns 0 when s & t are identical otherwise 1.
     */
    int i;
    for (i = 0; s[i] != 0 || t[i] != 0; i++)
        if (s[i] != t[i])
            return 1;

    if (s[i] != t[i])
        return 1;
    return 0;
}


int main() {
    char s[BUF_SIZE];
    char _s[BUF_SIZE];

    /* 65535 : _s & s = "65535" (pass) */
    unsigned short ushort_max = ~0;
    itoa(ushort_max, s);
    _itoa(ushort_max, _s);
    assert(str_cmp(s, "65535") == 0);
    assert(str_cmp(_s, "65535") == 0);

    /* -32768 : _s & s = "-32768" (pass) */
    short short_min = (short) (1 << ((sizeof(short) * CHAR_BIT) - 1));
    itoa(short_min, s);
    _itoa(short_min, _s);
    assert(str_cmp(s, "-32768") == 0);
    assert(str_cmp(_s, "-32768") == 0);

    /* 2147483647 : _s & s = "2147483647" (pass) */
    int int_max = ~(1 << ((sizeof(int) * CHAR_BIT) - 1));
    itoa(int_max, s);
    _itoa(int_max, _s);
    assert(str_cmp(s, "2147483647") == 0);
    assert(str_cmp(_s, "2147483647") == 0);

    /* -2147483648 :  s != "-2147483648" & _s = "-2147483648" */
    int int_min = (1 << ((sizeof(int) *  CHAR_BIT) - 1));
    itoa(int_min, s);
    assert(str_cmp(s, "-2147483648") == 1);  // fail
    _itoa(int_min, _s);
    assert(str_cmp(_s, "-2147483648") == 0);  // pass
}
