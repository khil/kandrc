#include <stdio.h>

/*
 * Exercise 1-15.  rewrite the temperature conversion of section 1.2 to
 * use a function for conversion.
*/

float fahr_to_celsius(float f_val);

int main() {
    float fahr;

    printf("Farh Celsius\n---- -------\n");
    for (fahr = 0; fahr <= 300; fahr = fahr + 30) {
        printf("%4.0f %6.1f\n", fahr, fahr_to_celsius(fahr));
    }
}

float fahr_to_celsius(float f_val) {
	return (5.0/9.0) * (f_val - 32.0);
}
