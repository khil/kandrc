#include <stdio.h>

/*
 * Exercise 1-4.  Write a program to print the corresponding Celsius to Fahrenheit
 * table.
*/
int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 30;
    celsius = lower;

    printf("Celsius Farh\n------- ----\n");
    while (celsius <= upper) {
        fahr = (celsius * 9.0/5.0) + 32.0;
        printf("%6.0f %4.0f\n", celsius, fahr);
            celsius = celsius + step;
    }
}
