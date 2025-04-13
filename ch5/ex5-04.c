#include <assert.h>
#include <string.h>

/*
 * Exercise 5-4. Write a function strend(s,t) which returns 1 if the string 
 * t occurs at the end of the string s, and zero otherwise.
 */

int strend(char *s, char *t) {
    size_t ls = strlen(s),
           lt = strlen(t);
    if (ls >= lt) {
        s += ls - lt;
        for (; *s == *t; s++, t++)
            if (*s == 0 && *t == 0)
                return 1;
    }
    return 0;
}


int main() {

    char s[100] = "Hello, world!";
    assert(strend(s, "x") == 0);
    assert(strend(s, "ld!") == 1);
    assert(strend("", "") == 1);
    assert(strend("", "ld!") == 0);
    assert(strend("ldi", "ld!") == 0);

    return 0;
}
