#include <assert.h>

/*
 * Exercise 3-2. Write a function expand(s1, s2) that expands shorthand notations
 * like a-z in the string s1 into the equivalent complete list abc...xyz in s2.
 * Allow for letters of either case and digits, and be prepared to handle cases
 * lik a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken
 * literally.
 */
#define BUF_SIZE 5000
#define UPPER_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER_ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define NUMBER_SEQ "0123456789"


int append_at(char s[], const unsigned p, const char s2[]) {
    int i, j;
    for (i = 0, j = p; s2[i] != 0; i++, j++)
        s[j] = s2[i];
    return j-p-1;
}


void expand(const char s1[], char s2[]) {
    /*
     * Assumes there is sufficient buffer space in s2 to add additional characters.
     * No checking is performed.
     */
    int i, j;
    for (i = 0, j = 0; s1[i] != 0; i++, j++) {
        switch (s1[i]) {
            case 'a':
                if (s1[i+1] == '-' && s1[i+2] == 'z') {
                    j += append_at(s2, j, LOWER_ALPHABET);
                    i+=2;
                    break;
                }
            case 'A':
                if (s1[i+1] == '-' && s1[i+2] == 'Z') {
                    j += append_at(s2, j, UPPER_ALPHABET);
                    i+=2;
                    break;
                }
            case '0':
                if (s1[i+1] == '-' && s1[i+2] == '9') {
                    j += append_at(s2, j, NUMBER_SEQ);
                    i+=2;
                    break;
                }
            default:
                s2[j] = s1[i];
        }
    }
    s2[j] = 0;
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
    const char *str1 = "This is a test: -a-z ... 0-9; some more bullshit A-Z.  The end!";
    char str2[BUF_SIZE];

    expand("a-z", str2);
    assert(str_cmp(str2, LOWER_ALPHABET) == 0);

    expand("A-Z", str2);
    assert(str_cmp(str2, UPPER_ALPHABET) == 0);

    expand("0-9", str2);
    assert(str_cmp(str2, NUMBER_SEQ) == 0);

    expand("-a-z-0-9-A-Z-", str2);
    assert(str_cmp(str2, "-abcdefghijklmnopqrstuvwxyz-0123456789-ABCDEFGHIJKLMNOPQRSTUVWXYZ-") == 0);

    expand(str1, str2);
    assert(str_cmp(str2, "This is a test: -abcdefghijklmnopqrstuvwxyz ... 0123456789; some more bullshit ABCDEFGHIJKLMNOPQRSTUVWXYZ.  The end!") == 0);
}
