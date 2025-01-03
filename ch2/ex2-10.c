#include <assert.h>

/*
** Exercise 2-10. Rewrite the function lower, which converts upper case letters
** to lower case, with a conditional expression instead of if-else.
*/
int lower(int ch) {
    return ch >= 65 && ch <= 90 ? ch + 32 : ch;
}

int main() {
    /* ch = 0 (null) : unchanged */
    assert(lower(0) == 0);

    /* ch = 91 ([) : unchanged */
    assert(lower(91) == 91);

    /* ch=127 (DEL) : unchanged */
    assert(lower(127) == 127);

    /* ch=98 (b) : unchanged */
    assert(lower(98) == 98);

    /* ch=113 (q) : unchanged */
    assert(lower(113) == 113);

    /* ch=120 (x) : unchanged */
    assert(lower(120) == 120);

    /* ch=66 (B) : 98 (b) */
    assert(lower(66) == 98);

    /* ch=81 (Q) : 113 (q) */
    assert(lower(66) == 98);

    /* ch=88 (X) : 120 (x) */
    assert(lower(88) == 120);

    return 0;
}

