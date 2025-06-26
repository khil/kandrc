#include <assert.h>
#include "../str.h"

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 * Rewrite of exercise 3-2. Write a function escape(s,t) that converts char-
 * acters like newline and tab into visible escape sequences like \n and \t as
 * it copies the string t to s.  Use a switch.  Write a function for the other
 * direction as well, converting escape sequences into the real characters.
 */
#define BUF_SIZE 5000


char *escape_p(char *s, const char *t) {
    char *q = s;

    for (char *p = (char *) t; *p; p++, q++) {
        switch (*p) {
            case '\n':
                *q++ = '\\';
                *q = 'n';
                break;
            case '\t':
                *q++ = '\\';
                *q = 't';
                break;
            default:
                *q = *p;
                break;
        }
    }
    *q = 0;

    return q;
}


char *unescape_p(char *s, const char *t) {
    char *q = s;

    for (char *p = (char *) t; *p; p++, q++) {
        switch (*p) {
            case '\\':
                if (*(p+1) == 'n') {
                    *q = '\n';
                    p++;
                    break;
                } else if (*(p+1) == 't') {
                    *q = '\t';
                    p++;
                    break;
                }
                /* Intentional fall through to the 'default' label to handle 
                 * escape sequences other than \n & \t.
                 */
            default:
                *q = *p;
                break;
        }

    }
    *q = 0;

    return q;
}


int32_t main() {
    char original_t[BUF_SIZE] = "\\This is a test:\n\tTest...\n\tTest...\n\tTesticles!\n";
    char escaped_s[BUF_SIZE];
    char unescaped_s[BUF_SIZE];
    const char *escaped_check_str = "\\This is a test:\\n\\tTest...\\n\\tTest...\\n\\tTesticles!\\n";

    escape_p(escaped_s, original_t);
    unescape_p(unescaped_s, escaped_s);

    assert(_strcmp(escaped_s, escaped_check_str) == 0);
    assert(_strcmp(original_t, unescaped_s) == 0);
}
