#include <assert.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 3-3. Write a function expand(s1, s2) that expands short-
 * hand notations like a-z in the string s1 into the equivalent complete list
 * abc...xyz in s2. Allow for letters of either case and digits, and be prepared
 * to handle cases lik a-b-c and a-z0-9 and -a-z. Arrange that a leading or
 * trailing - is taken literally.
 */
#define BUF_SIZE 5000
#define UPPER_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER_ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define NUMBER_SEQ "0123456789"


char *append_at(char *d, char *a) {
    for (; *a; a++, d++)
        *d = *a;
    d--;

    return d;
}


char *expand(const char *s1, char *s2) {
    char *d = s2;
    for(char *s = (char *) s1; *s; s++, d++) {
        switch(*s) {
            case 'a':
                if(*(s+1) == '-' && *(s+2) == 'z') {
                    d = append_at(d, LOWER_ALPHABET);
                    s+=2;
                    break;
                }
            case 'A':
                if(*(s+1) == '-' && *(s+2) == 'Z') {
                    d = append_at(d, UPPER_ALPHABET);
                    s+=2;
                    break;
                }
            case '0':
                if(*(s+1) == '-' && *(s+2) == '9') {
                    d = append_at(d, NUMBER_SEQ);
                    s+=2;
                    break;
                }
            default:
                *d = *s;
        }
    }
    *d = 0;

    return d;
}


int32_t main() {
    const char *str1 = "This is a test: -a-z ... 0-9; some more bullshit A-Z.  The end!";
    char str2[BUF_SIZE];

    expand("a-z", str2);
    assert(_strcmp(str2, LOWER_ALPHABET) == 0);

    expand("A-Z", str2);
    assert(_strcmp(str2, UPPER_ALPHABET) == 0);

    expand("0-9", str2);
    assert(_strcmp(str2, NUMBER_SEQ) == 0);

    expand("-a-z-0-9-A-Z-", str2);
    assert(_strcmp(str2, "-abcdefghijklmnopqrstuvwxyz-0123456789-ABCDEFGHIJKLMNOPQRSTUVWXYZ-") == 0);

    expand(str1, str2);
    assert(_strcmp(str2, "This is a test: -abcdefghijklmnopqrstuvwxyz ... 0123456789; some more bullshit ABCDEFGHIJKLMNOPQRSTUVWXYZ.  The end!") == 0);
}
