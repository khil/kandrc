#include <stdio.h>
#include <assert.h>

/*
** Exercise 2-9. In a two's compliment number system, x &= (x-1) deletes the
** rightmost 1-bit in x. Explain why. Use this observation to write a faster
** version of bitcount.
*/


int bit_count(unsigned x) {
    int b;

    for (b = 0; x != 0; x &= (x-1)) {
        printf("x=%u\n", x);
        b++;
    }

    return b;
}

int bitcount(unsigned x) {
    int b;

    for (b = 0; x != 0; x >>= 1) {
        if (x & 01)
            b++;
    }

    return b;
}

int main() {

    /* test -> x=11111110 */
    assert((bitcount(254) == 7) && (bit_count(254) == 7));

    /* test -> x=1000010000000111 */
    assert((bitcount(33799) == 5) && (bit_count(33799) == 5));

    /* test -> x=1100010000100111 */
    assert((bitcount(50215) == 7) && (bit_count(50215) == 7));

    /* test -> x=1000000000000001 */
    assert((bitcount(32769) == 2) && (bit_count(32769) == 2));

    /* test -> x=1010101010101010 */
    assert((bitcount(43690) == 8) && (bit_count(43690) == 8));

    return 0;
}

