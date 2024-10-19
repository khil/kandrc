#include <stdio.h>

/*
 * Exercise 1-3.  Modify the temperature conversion to print a heading
 * above the table
*/

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 30;
    fahr = lower;

    printf("Farh Celsius\n---- ------\n");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr - 32.0);
        printf("%4.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}
