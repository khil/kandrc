#include <assert.h>

#define swap(t,x,y) { t _t; _t = x; x = y; y = _t; }

/* 
 * Exercise 4-14.  Define a macro swap(t,x,y) that interchanges two arguments
 * of type t. (block structure will help.)
 */

int main() {

    int a = 1, b = 2;
    swap(typeof(int), a, b);
    assert(a==2 && b==1);

    double f = 12.76, g = 25.52;
    swap(typeof(f), f, g);
    assert(f==25.52 && g == 12.76);


    return 0;
}
