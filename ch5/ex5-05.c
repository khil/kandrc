#include <assert.h>
#include <stdio.h>
#include <string.h>

/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 */

char *_strncpy(char *dst, char *src, size_t n) {
    char * res = dst;
    for (int i = 0; *src; i++, src++, dst++)
        *dst = *src;
    *dst = 0;
    return dst;
}

char *_strncat(char *dst, char *src, size_t n) {
    char *res = dst;
    dst += strlen(dst);
    for (int i = 0; i < n && *src; i++, src++, dst++)
        *dst = *src;
    *dst = 0;
    return res;
}

int _strncmp(char *s, char *t, size_t n) {
    int i;
    for (i = 0; i < n && *s == *t; i++, s++, t++)
        if (s == 0)
            return -1;
        else if (t == 0)
            return 1;
    if (i == n) {
        s--;
        t--;
    }
    if (*s == *t)
        return 0;
    else
        return (*s - *t);
}


int main() {

    char s[100] = "Hello, world!";
    printf("%d\n", _strncmp("", "", 1));
    printf("%d\n", _strncmp("abcd", "abce", 3));
    printf("%d\n", _strncmp("aa", "bb", 1));
    printf("%d\n", _strncmp("bb", "aa", 1));

    _strncat(s, "; goodbye", 6);
    printf("s=%s\n", s);
    s[0] = 0;
    
    printf("s=%s\n", _strncat(s, "testicular cancer sucks!", 4));

    s[0] = 0;
    printf("s=%s\n", _strncat(s, "this is a test!", 9));

    return 0;
}
