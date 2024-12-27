#include <stdio.h>
#include <assert.h>

/*
** Exercise 2-7. Write a function invert(x,p,n) that returns x with the bits
** that begin at position p inverted (i.e., 1 changed to 0 and vise versa), leaving
** the others unchanged.
*/

unsigned invert(unsigned x, unsigned p, unsigned n) {
    /*     |----------- step 3 below -----------| */
    /*         |--------- step 2 below ---------| */
    return x ^ ~(~0 << (p+1) | ~(~0 << (p+1-n))); 
}

unsigned _invert(unsigned x, unsigned p, unsigned n) {
    /*
    **  This is a rewrite of the one-liner above with parameter checking and a description of
    **  what's going on.
    **  
    **  Parameters:
    **      x - Value for which the bits are to be replaced and returned.
    **      p - Position of the starting bit (rightmost bit = 0). Valid values include, 0 to
    **          sizeof(unsigned) * 8 - 1.
    **      n - For x, the number of bits to the right of p to replace. For y, the number of bits,
    **          from the rightmost bit to copy into x. Valid values 0 to p + 1. Note: if n = Zero
    **          there's nothing to do.
    **      y - Source value from which to get n bits.
    **
    **  Assuming (using 8 bits for simplicity):
    **      x = 10011011 (155)
    **      p = 6
    **      n = 3
    **
    **  1. Validate the ranges of p & n.
    **  2. Create a mask to isolate the bits we want to retain from x. To achieve this create two
    **     temporary masks, one for the left side bits and one for the right. The two temporary
    **     masks will be combined into a single mask using a bitwise AND operation.
    **     a. The left mask should retain the bit(s) on left side of p+1. To make the mask start
    **        with a NOT 0 (~0), then shifting the bits left p+1 positions; the result should be:
    **        10000000
    **     b. The right mask needs to retain the bit(s) to the right of the index p+1-n. To make
    **        the mask start with (~0) and shifting the bits to the right by p+1-n. i.e.,
    **        11110000. Then bitwise NOT the result, i.e., 00001111.
    **     c. The next step to create the mask is to bitwise OR the left and right masks with the
    **        result being: 10001111.
    **     d. The final step is to bitwise NOT(~) the mask created in 3c to make the mask 01110000.
    **  3. Bitwise XOR x and the mask created in step 3 returning the result, i.e., 11101011.
    */
    if (n == 0) /* 1: early exit - nothing to do */
        return x;

    if ((p >= 0 && p <= (sizeof(unsigned) * 8) - 1) && (n >= 1 && n <= p+1)) { /* 1 */
        unsigned left_bits = ~0 << (p+1);                               /* 2a */
        unsigned right_bits = ~(~0 << (p+1-n));                         /* 2b */
        return x ^ ~(left_bits | right_bits);                           /* 3, 2c, & 2d */
    }
    else
        return 0;
}


int main() {

    /* p=too big (not handled properly by invert -> x=10011011 : 1(110)1011 */
    assert((invert(155, 0xFFFFFFFF, 3) != 0) && (_invert(155, 4294967295, 3) == 0));    

    /* n=0 (nothing to do) -> x=10011011 : 11101011 */
    assert((invert(155, 6, 0) == 155) && (_invert(155, 6, 0) == 155));    

    assert((invert(155, 6, 3) == 235) && (_invert(155, 6, 3) == 235));    
    /* std -> x=1(001)1011 : 1(110)1011 */
    assert((invert(235, 3, 2) == 231) && (_invert(235, 3, 2) == 231));    

    /* std test -> x=00000(01)0 : equal to x */
    assert((invert(2, 2, 2) == 4) && (_invert(2, 2, 2) == 4));    

    /* std test -> x=0000(1)111 : 0000(0)111 */
    assert((invert(15, 3, 1) == 7) && (_invert(15, 3, 1) == 7));    

    /* std test -> x=0011(01)11 : 0011(10)11 */
    assert((invert(55, 3, 2) == 59) && (_invert(55, 3, 2) == 59));
    
    /* std test -> x=(00110111) : equal to y */
    assert((invert(55, 7, 8) == 200) && (_invert(55, 7, 8) == 200)); 

    /* std test -> x=1111(1111) : 1111(0000) */
    assert((invert(255, 3, 4) == 240) && (_invert(255, 3, 4) == 240)); 

    /* std test -> x=1111111(1) : 1111111(0) */
    assert((invert(255, 0, 1) == 254) && (_invert(255, 0, 1) == 254)); 

    return 0;
}

