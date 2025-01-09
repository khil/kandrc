#include <assert.h>
#include <stdlib.h>
#include <time.h>


/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside). Write a version with 
 * only one test inside the loop and measure the difference in run-time.
 */

unsigned bin_search(unsigned x, unsigned v[], unsigned n) {
    /* Eliminated the second test from the loop, even with a large array (2
     * million) elements no noticeable difference in run-time was observed.
     */
    unsigned low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if (x == v[mid])
        return mid;
    else
        return -1;
}


unsigned binsearch(unsigned x, unsigned v[], unsigned n) {
    /* the original function as provided in the book */
    unsigned low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
           return mid;
    }

    return -1;
}


void populate_array(unsigned arr[], unsigned n) {
    /* populate the array with n numbers, the base value is a PRN between 0-9
     * and each subsequent value is increased by the step, also a PRN between
     * 1-5
     */
    unsigned val = rand() % 10; /* range 0 and 9 */
    unsigned step = rand() % 6; /* range 0 and 5 */
    if (!step)
        step = 1;
    
    for(unsigned i = 0; i < n; i++, val+=step)
        arr[i] = val;
}


int main() {
    srand(time(NULL));              /* Initialize PRNG */
    unsigned n = 2000000;           /* 2 million elements for out array */
    unsigned v[n];                  /* allocate and populate the array */
    populate_array(v, n);
    unsigned x = rand() % v[n-1];   /* generate the number to find in the array */

    assert(binsearch(x, v, n) == bin_search(x, v, n));
}
