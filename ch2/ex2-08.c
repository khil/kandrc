#include <assert.h>
#include <limits.h>

/*
** Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
** integer x rotated to the right by n bit operations.
*/

typedef unsigned char ubyte;


ubyte rightrot(ubyte x, ubyte n) {
    /*
    **  Note: the size of the parameters (in bytes) impacts the result. For simplicity
    **         one byte is use.
    **
    **  Parameters:
    **      x - Value for which the bits are to be rotated to the right.
    **      n - For x, the number of bits to the right to rotate the bits.
    **
    **  Assuming (using 8 bits for simplicity):
    **      x = 10011011 (155)
    **      n = 3
    **
    **  1. Validate n is > 0 and < 8.
    **  2. Create a mask to extract n bits from the right of x (mask=00000111); Then extract the
    **     bits using a bitwise AND between x and the mask resulting in: 00000011.
    **  3. Shift r to the left by sizeof(ubyte) * 8 - n bits, 01100000
    **  4. Shift x by n bits to the right, 00010011
    **  5. Return the bitwise OR of X and result or step 3.
    */
    if (n > 0 && n < sizeof(ubyte) * CHAR_BIT) {
        ubyte res = x & ~(~0 << n);
        res <<= (sizeof(ubyte) * CHAR_BIT) - n;
        x >>= n;
        return x | res;
    } else 
        return x;
}


int main() {

    /* n=0 (nothing to do) -> x=10011011 : 11101011 */
    assert(rightrot(155, 0) == 155);

    /* n=9 (n too big) -> x=10011011 : 11101011 */
    assert(rightrot(155, 9) == 155);

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

