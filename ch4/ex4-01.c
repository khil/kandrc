#include <assert.h>

/* 
 * Exercise 4-1.  Write a function strrindex(s,t) which returns  the position
 * of the rightmost occurrence of t in s, or -1 if there is none.
 */

int strrindex(char s[], const char t[]) {
    int i, j, idx = -1;

    for (i = 0; s[i] != 0; i++) {
        if (s[i] == t[0]) {
            for (j = 1; t[j] != 0; j++)
                if (s[i+j] != t[j])
                    break;
            
            if (t[j] == 0)
                idx = i;
        }
    }

    return idx;
}

int strindex(char s[], const char t[]) {
    int i, j;

    for (i = 0; s[i] != 0; i++) {
        if (s[i] == t[0]) {
            for (j = 1; t[j] != 0; j++)
                if (s[i+j] != t[j])
                    break;
            
            if (t[j] == 0)
                return i;
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
