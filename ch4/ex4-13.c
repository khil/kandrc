#include <assert.h>
#include <string.h>

/* 
 * Exercise 4-13.  Write a recursive version of the furnction reverse(s), which
 * reverses the string in place.
 */

void _reverse(char s[], int i) {
    int len = strlen(s);
    if (i < len / 2) {
		int c = s[0+i];
		s[0+i] = s[len - i - 1];
		s[len - i - 1] = c;
        _reverse(s, ++i);
    }
}

void reverse(char s[]) {
    _reverse(s, 0);
}


int main() {
    char s[100] = "olleh";

    reverse(s);
    assert(strcmp(s, "hello") == 0);

    strcpy(s, "!tset a si sihT");
    reverse(s);
    assert(strcmp(s, "This is a test!") == 0);

    return 0;
}
