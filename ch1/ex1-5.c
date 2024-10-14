#include <stdio.h>

/*
 * Exercise 1-5.  Modify the temperature conversion to print the table in
 * reverse order, that is from 300 degrees to 0.
*/

int main() {
	float celsius;
    printf("Celius Farh\n------ ----\n");
    for (celsius = 300.0; celsius >= 0; celsius = celsius - 30) {
        printf("%6.0f %4.0f\n", celsius, ((celsius * 9.0/5.0) + 32.0));
    }
}
