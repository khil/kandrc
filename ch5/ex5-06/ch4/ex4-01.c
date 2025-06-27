#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "../str.h"

/* 
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Exercise 4-1.  Write a function strrindex(s,t) which returns the position
 * of the rightmost occurrence of t in s, or -1 if there is none.
 */

int32_t strrindex(const char *s, const char *t) {

    size_t t_len = _strlen(t) - 1;
    char *q, *end = (char *) (t + t_len);

    for (char *p = (char *) (s + _strlen(s) - 1); p - s >= 0; p--) {
        if(*p == *end) {
            for (q = end-1; end-q >= 0; q--) {
                if (*(p-(end-q)) != *q)
                    break;
            }
            if (end - q == t_len+1) {
                p -= t_len;
                return p - s;

            }
        }
    }

    return -1;
}


int32_t strindex(const char *s, const char *t) {
    char *q;

    for (char *p = (char *) s; *p; p++) {
        if (*p == *t) {
            for (q = (char *)t+1; *q; q++) {
                if (*(p+(q-t)) != *q)
                    break;
            }
            if (!*q)
                return p - s;
        }
    }

    return -1;
}

int main() {
              /*  0000000000111111111122222222223333333333444444444455555555556666666666777777777788888888889
                  0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890 */
    char *test = "ABCDEFGxHIJKLMNOPQRSTUVWxyXYZabcdefghijklmnopqrstuvwxyzABCxyzDEFGHIJKLMNOPQRSTUVWXYZxyzpdq";
    assert(strindex(test, "xyz") == 52);

    assert(strrindex(test, "qqq") == -1);

    assert(strrindex(test, "xyz") == 84);

    return 0;
}
