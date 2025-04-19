#include <assert.h>
#include <string.h>

/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 */

char *_strncpy(char *dst, char *src, size_t n) {
    char *res = dst;
    for (int i = 0; i < n && *src; i++, src++, dst++)
        *dst = *src;
    *dst = 0;
    return res;
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
    return (*s == *t) ? 0 : (*s - *t);
}


int main() {

    assert(_strncmp("", "", 1) == 0);
    assert(_strncmp("abcd", "abce", 3) == 0);
    assert(_strncmp("aa", "bb", 1) < 0);
    assert(_strncmp("hello", "help", 4) < 0);
    assert(_strncmp("help", "hello", 4) > 0);
    assert(_strncmp("bb", "aa", 1) > 0);

    char s[100], t[100];
    char *hello = "Hello, world!";
    assert(strcmp(_strncpy(s, hello, 99), hello) == 0);
    assert(strcmp(_strncat(s, "; goodbye", 6), "Hello, world!; good") == 0);

    s[0] = 0;
    char *temp = "testicular cancer sucks!";
    assert(strcmp(_strncat(s, temp, 4), "test") == 0);
    assert(strcmp(_strncat(s, "; this is a test!", 11), "test; this is a") == 0);

    assert(strcmp(_strncpy(t, s, 5), "test;") == 0);

    return 0;
}
