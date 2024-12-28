#include <assert.h>

/*
** Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
** integer x rotated to the right by n bit operations.
*/

typedef unsigned char ubyte;


ubyte rightrot(ubyte x, ubyte n) {
    /*
    **  This is a rewrite of the one-liner above with parameter checking and a description of
    **  what's going on.
    **  
    **  Parameters:
    **      x - Value for which the bits are to be replaced and returned.
    **      p - Position of the starting bit (rightmost bit = 0). Valid values include, 0 to
    **          sizeof(ubyte) * 8 - 1.
    **      n - For x, the number of bits to the right of p to replace. For y, the number of bits,
    **          from the rightmost bit to copy into x. Valid values 0 to p + 1. Note: if n = Zero
    **          there's nothing to do.
    **
    **  Assuming (using 8 bits for simplicity):
    **      x = 10011011 (155)
    **      p = 6
    **      n = 3
    **
    **  1. Validate the ranges of p & n.
    **  2. Create a mask to isolate the bits we want to retain from x. To achieve this create two
    **     temporary masks, one for the left side bits and one for the right. The two temporary
    **     masks will be combined into a single mask using a bitwise OR operation.
    **     a. The left mask should retain the bit(s) on left side of p+1. To make the mask start
    **        with a NOT 0 (~0), then shifting the bits left p+1 positions; the result should be:
    **        10000000
    **     b. The right mask needs to retain the bit(s) to the right of the index p+1-n. To make
    **        the mask start with (~0) and shifting the bits to the right by p+1-n. i.e.,
    **        11110000. Then bitwise NOT the result, i.e., 00001111.
    **     c. The next step is to create the mask is bitwise ORing the left and right masks, the
    **        result being: 10001111.
    **     d. The final step is to bitwise NOT(~) the mask created in 3c to make the mask 01110000.
    **  3. Bitwise XOR x and the mask created in step 3 returning the result, i.e., 11101011.
    */
    if (n == 0) /* 1: early exit - nothing to do */
        return x;

    ubyte mask = ~(~0 << n);
    ubyte res = x & mask;
    x >>= n;
    res <<= (sizeof(ubyte) * 8) - n;
    return x | res;
}


int main() {

    /* n=0 (nothing to do) -> x=10011011 : 11101011 */
    assert(rightrot(155, 0) == 155);

    /* std -> x=10011(011) : (011)10011*/
    assert(rightrot(155, 3) == 115);

    /* std -> x=111010(11) : (11)111010  */
    assert(rightrot(235, 2) == 250);

    /* std test -> x=000000(10) : (10)000000 */
    assert(rightrot(2, 2) == 128);

    /* std test -> x=0000111(1) : (1)0000111 */
    assert(rightrot(15, 1) == 135);

    /* std test -> x=001101(11) : (11)001101 */
    assert(rightrot(55, 2) == 205);
    
    /* std test -> x=0011(0111) : (0111)0011 */
    assert(rightrot(55, 4) == 115);

    /* std test -> x=1111(1010) : (1010)1111 */
    assert(rightrot(250, 4) == 175);

    /* std test -> x=1111111(0) : (0)1111111 */
    assert(rightrot(254, 1) == 127);

    return 0;
}

