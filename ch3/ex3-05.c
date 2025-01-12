#include <assert.h>

/*
 * Exercise 3-5. Write a function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s.  In particular,
 * itob(n,s,16) formates n as a hexadecimal integer in s.
 */

#define BUF_SIZE 100
#define BASE_CHARS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ERROR_MSG "ERROR: Invalid Base Specified!"


int str_len(const char s[]) {
    /* A quick & dirty implementation of strlen (string length).
     * The number of characters copied is returned
     */
    int len;
    for(len=0; s[len] != 0; ++len);
    return len;
}


void reverse(char s[]) {
    /* reverse string */
    int len = str_len(s);
    len--;

    for(int i=0, c; i <= (len / 2); i++) {
		c = s[i];
		s[i] = s[len - i];
		s[len - i] = c;
    }
}


int _abs(int v) {
    /* simple absolute value function */
    return v < 0 ? -v : v;
}


int str_cpy(char s[], const char t[]) {
    /* A quick & dirty implementation of strcpy (string copy).
     * The number of characters copied is returned
     */
    int i;
    for (i = 0; t[i] != 0; i++)
        s[i] = t[i];
    return 1;
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


void itob(int n, char s[], const unsigned char b) {
    /* handles conversions up to base-36 */
    if (b > 1 && b <= str_len(BASE_CHARS)) {
        int i = 0, sign = n;

        do {
            s[i++] = BASE_CHARS[_abs(n % b)];
        } while((n /= b) != 0);
        if (sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        reverse(s);
    }
    else
        str_cpy(s, ERROR_MSG);
}


int main() {
    char s[BUF_SIZE];

    itob(143, s, 46);
    assert(str_cmp(s, ERROR_MSG) == 0);

    itob(143, s, 36);
    assert(str_cmp(s, "3Z") == 0);

    itob(143, s, 16);
    assert(str_cmp(s, "8F") == 0);

    itob(143, s, 8);
    assert(str_cmp(s, "217") == 0);

    itob(143, s, 2);
    assert(str_cmp(s, "10001111") == 0);

    itob(-143, s, 8);
    assert(str_cmp(s, "-217") == 0);

    itob(0256, s, 8);
    assert(str_cmp(s, "256") == 0);

    itob(0b11111111, s, 16);
    assert(str_cmp(s, "FF") == 0);

    itob(0xFF, s, 2);
    assert(str_cmp(s, "11111111") == 0);

    itob(0xFFFF, s, 2);
    assert(str_cmp(s, "1111111111111111") == 0);

    return 0;
}
