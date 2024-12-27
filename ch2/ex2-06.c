#include <assert.h>

/*
** Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
** bits that begin at position p set to the rightmost n bits of y, leaving the
** other bits unchanged.
*/

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
    /*     |------------------------- step 4 below -------------------------| */
    /*     |---------- step 2 below ----------|   | ----- step 3 below -----| */
    return x & (~0 << (p+1) | ~(~0 << (p+1-n))) | (y & ~(~0 << n)) << (p+1-n);
}

unsigned set_bits(unsigned x, unsigned p, unsigned n, unsigned y) {
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
    **      y = 11100110 (230)
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
    **     c. The final step to create the mask is bitwise OR the left and right masks with the
    **        result being: 10001111.
    **     d. Bitwise AND x and the final mask created in 3c to get our final result. i.e,
    **        10001011.
    **  3. Create a second mask to extract n bits from the right of y.
    **     a. Start with ~0 and shift it right n bits, i.e., 11111000, then bitwise NOT the result
    **        to achieve 00000111.
    **     b. Then bitwise AND the result achieved in 3a with y to give you the bits to be copied
    **        into x, i.e., 00000110
    **     c. Shift the result achieved in 3b by p+1-n bits to the right to align the mask with
    **        the insertion point in x. i.e., 01100000
    **  4. Bitwise OR the results of 2d and 3c to return our final result, i.e., 11101011 (235)
    */
    if (n == 0 || (x == 0 && y == 0)) /* 1: early exit - nothing to do */
        return x;

    if ((p >= 0 && p <= (sizeof(unsigned) * 8) - 1) && (n >= 1 && n <= p+1)) { /* 1 */
        unsigned left_bits = ~0 << (p+1);                               /* 2a */
        unsigned right_bits = ~(~0 << (p+1-n));                         /* 2b */
        unsigned x_res = x & (left_bits | right_bits);                  /* 2c & 2d */

        unsigned y_mask = (~(~0 << n));                                 /* 3a & 3b */
        unsigned y_res = (y & y_mask) << (p+1-n);                       /* 3c */

        return x_res | y_res;                                           /* 4 */
    }
    else
        return 0;
}


int main() {

    /* p=too big (not handled properly by setbits -> x=10011011    y=11100(110) : 1(110)1011 */
    assert((setbits(155, 0xFFFFFFFF, 3, 230) != 0) && (set_bits(155, 4294967295, 3, 230) == 0));    

    /* x=y=0 (nothing to do) -> x=0(000)0000    y=00000(000) : 0(000)0000 */
    assert((setbits(0, 6, 3, 0) == 0) && (set_bits(0, 6, 3, 0) == 0));    

    /* n=0 (nothing to do) -> x=10011011    y=11100110 : 11101011 */
    assert((setbits(155, 6, 0, 230) == 155) && (set_bits(155, 6, 0, 230) == 155));    

    /* std -> x=1(001)1011    y=11100(110) : 1(110)1011 */
    assert((setbits(155, 6, 3, 230) == 235) && (set_bits(155, 6, 3, 230) == 235));    

    /* std test -> x=00000(01)0  y=000011(01) : equal to x */
    assert((setbits(2, 2, 2, 13) == 2) && (set_bits(2, 2, 2, 13) == 2));    

    /* std test -> x=0000(1)111  y=0000111(0) : 0000(0)111 */
    assert((setbits(15, 3, 1, 14) == 7) && (set_bits(15, 3, 1, 14) == 7));    

    /* std test -> x=0011(01)11  y=010011(10) : 0011(10)11 */
    assert((setbits(55, 3, 2, 78) == 59) && (set_bits(55, 3, 2, 78) == 59));
    
    /* std test -> x=(00110111)  y=(01001110) : equal to y */
    assert((setbits(55, 7, 8, 78) == 78) && (set_bits(55, 7, 8, 78) == 78)); 

    /* std test -> x=1111(1111)  y=0000(0000) : 1111(0000) */
    assert((setbits(255, 3, 4, 0) == 240) && (set_bits(255, 3, 4, 0) == 240)); 

    /* std test -> x=1111111(1)  y=0000000(0) : 1111111(0) */
    assert((setbits(255, 0, 1, 0) == 254) && (set_bits(255, 0, 1, 0) == 254)); 

    return 0;
}

