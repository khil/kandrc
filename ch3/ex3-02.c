#include <assert.h>

/*
 * Exercise 3-2. Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies the
 * string t to s.  Use a switch.  Write a function for the other direction as well,
 * converting escape sequences into the real characters.
 */
#define BUF_SIZE 5000


void escape(char s[], const char t[]) {
    /*
     * Assumes there is sufficient buffer space to add additional characters to
     * s. No checking is performed
     */
    int i, j;
    for (i = 0, j = 0; t[i] != 0; i++, j++) {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j] = 't';
                break;
            default:
                s[j] = t[i];
                break;
        }
    }
    s[j] = 0;
}


void unescape(char s[], const char t[]) {
    int i, j;
    for (i = 0, j = 0; t[i] != 0; i++, j++) {
        switch (t[i]) {
            case '\\':
                if (t[i+1] == 'n') {
                    s[j] = '\n';
                    i++;
                    break;
                } else if (t[i+1] == 't') {
                    s[j] = '\t';
                    i++;
                    break;
                }
                /* Intentional fall through to the 'default' label to handle 
                 * escape sequences other than \n & \t.
                 */
            default:
                s[j] = t[i];
                break;
        }
    }
    s[j] = 0;
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
    char original_t[BUF_SIZE] = "\\This is a test:\n\tTest...\n\tTest...\n\tTesticles!\n";
    char escaped_s[BUF_SIZE];
    char unescaped_s[BUF_SIZE];
    const char *escaped_check_str = "\\This is a test:\\n\\tTest...\\n\\tTest...\\n\\tTesticles!\\n";

    escape(escaped_s, original_t);
    unescape(unescaped_s, escaped_s);

    assert(str_cmp(escaped_s, escaped_check_str) == 0);
    assert(str_cmp(original_t, unescaped_s) == 0);
}
