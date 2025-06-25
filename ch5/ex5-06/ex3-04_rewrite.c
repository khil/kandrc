#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 3-04, itoa, itof and reverse functions using pointers
 * also contains rewrite of 4-02 with atof.
 */

#define BUF_SIZE 100

size_t _strlen(char *s) {
    size_t i = 0;
    
    for (; *s; s++, i++)
        ;

    return i;
}

char *reverse(char *s) {
    if (s) {
        char *str = s;
        char *end = s + strlen(s) - 1;
        char tmp;

        for (; str < end; str++, end--) {
            tmp = *str;
            *str = *end;
            *end = tmp;
        }
    }

    return s;
}


int32_t _abs(int32_t v) {
    return v < 0 ? -v : v;
}


int almost_eq(double x, double y, double eps) {
    return (x - y) <= eps;
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


double _atof(char *s) {
    double val, power;
    int32_t sign;

    while (isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-')
        s++;

    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');

    if (*s == '.')
        s++;

    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }

    val = sign * val / power;

    /* handle scientific notation */
    if (tolower(*s) == 'e') {
        s++;
        sign = (*s == '-') ? -1 : 1;

        if (*s == '+' || *s == '-')
            s++;
        int n;
        for (n=0; isdigit(*s); s++)
            n = 10 * n + (*s - '0');

        val = val * pow(10, (n * sign));
    }

    return val;
}


int32_t strcmp(const char *s, const char *t) {
    for (; *s == *t; s++, t++)
        if (*s == 0)
            return 0;

    return *s - *t;
}


int32_t main() {

    char s[BUF_SIZE];

    // 65535 : _s & s = "65535" (pass)
    uint16_t ushort_max = ~0;

    itoa(ushort_max, s);
    assert(strcmp(s, "65535") == 0);

    // -32768 : _s & s = "-32768" (pass)
    int16_t short_min = (short) (1 << ((sizeof(short) * CHAR_BIT) - 1));
    itoa(short_min, s);
    assert(strcmp(s, "-32768") == 0);

    // 2147483647 : _s & s = "2147483647" (pass)
    int32_t int_max = ~(1 << ((sizeof(int) * CHAR_BIT) - 1));
    itoa(int_max, s);
    assert(strcmp(s, "2147483647") == 0);

    // -2147483648 :  s != "-2147483648" & _s = "-2147483648"
    int32_t int_min = (1 << ((sizeof(int) *  CHAR_BIT) - 1));
    itoa(int_min, s);


    assert(strcmp(s, "-2147483648") == 0);

    assert(almost_eq(_atof("-7.56012"), -7.56, 0.00000001) == 1);

    assert(almost_eq(_atof("-7.56012"), -7.5601, 0.00000001) == 1);

    assert(almost_eq(_atof("7.56012"), 7.56012, 0.00000001) == 1);

    assert(almost_eq(_atof("7.5e-6"), 0.0000075, 0.00000001) == 1);
    
    assert(almost_eq(_atof("7.5E-6"), 0.0000075, 0.00000001) == 1);

    assert(almost_eq(_atof("7.5e+6"), 7500000, 0.000001) == 1);

    assert(almost_eq(_atof("7.5e6"), 7500000, 0.000001) == 1);

    return 0;
}
