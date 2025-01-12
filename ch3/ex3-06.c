#include <assert.h>
#include <limits.h>

/*
 * Exercise 3-6. write a version of itoa that accepts three arguments instead of
 * two.  The third argument is a minimum field width; the converted number must
 * be padded with blanks on the left if necessary to make it wide enough.
 */

#define BUF_SIZE 1000


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

void itoa(int n, char s[], unsigned short minw) {
    int i = 0, sign = n;

    do {
        s[i++] = _abs(n % 10) + '0';
    } while((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);

    if (i < minw) {
        int j, d = minw - i;
        // shift the characters to the right replacing it with a space
        for(j = i; j >= 0; j--) {
        	s[j+d] = s[j];
        	s[j] = ' ';
        }
        /* any positions untouched by the shift above, replace with spaces */
        for (int j = i+1; j < d; j++) {
            s[j] = ' ';
        }
    }
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

    /* 65535 : _s & s = "          65535" (pass) */
    unsigned short ushort_max = ~0;
    itoa(ushort_max, s, 15);
    assert(str_cmp(s, "          65535") == 0);

    /* -32768 : _s & s = "         -32768" (pass) */
    short short_min = (short) (1 << ((sizeof(short) * CHAR_BIT) - 1));
    itoa(short_min, s, 15);
    assert(str_cmp(s, "         -32768") == 0);

    /* 2147483647 : _s & s = "2147483647"  */
    int int_max = ~(1 << ((sizeof(int) * CHAR_BIT) - 1));
    itoa(int_max, s, 20);
    assert(str_cmp(s, "          2147483647") == 0);

    /* -2147483648 :  s != "-2147483648"  */
    int int_min = (1 << ((sizeof(int) *  CHAR_BIT) - 1));
    itoa(int_min, s, 0);
    assert(str_cmp(s, "-2147483648") == 0);
    
    return 0;
}
