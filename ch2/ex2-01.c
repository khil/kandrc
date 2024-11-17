#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

/*
** Exercise 2-1.  Write a program to determine the ranges of char, short, int,
** and long variables, both sighed and unsigned, by printing appropriate
** values from standard headers and by direct computation. Harder if you comp-
** ute them: determine the ranges of the various floating point types.
*/

#define FALSE 0
#define TRUE 1

unsigned long signed_upper(unsigned long value) {
	return (value / 2) - 1;
}


long signed_lower(unsigned long value) {
	return (value / 2) * -1;
}


void print_int_limits(char type_name[], int bits, long min, unsigned long max, unsigned long umax) {
	unsigned long ulimit = pow(2, bits);
	int overflowed = (ulimit == 0); // longs will overflow and flip the bits to 0 

	printf("(signed) %s [%d bits]:\n", type_name, bits);
	if (overflowed) {
		ulimit--; // flip the overflowed back to its upper limit
		printf("\tcalc'd  : %+ld -> +%ld\n", signed_lower(ulimit) -1, signed_upper(ulimit)+1);
	}
	else
		printf("\tcalc'd  : %+ld -> +%ld\n", signed_lower(ulimit), signed_upper(ulimit));

	printf("\tlimits.h: %+ld -> +%ld\n", min, max);
	printf("unsigned %s:\n", type_name);
	if (overflowed)
		printf("\tcalc'd  : 0 -> +%lu\n", ulimit);
	else
		printf("\tcalc'd  : 0 -> +%ld\n", ulimit - 1);
	printf("\tlimits.h: 0 -> +%lu\n", umax);

}

int main() {
	print_int_limits("char", __SCHAR_WIDTH__, CHAR_MIN, CHAR_MAX, UCHAR_MAX);
	print_int_limits("short", __SHRT_WIDTH__, SHRT_MIN, SHRT_MAX, USHRT_MAX);
	print_int_limits("int", __INT_WIDTH__, INT_MIN, INT_MAX, UINT_MAX);
	print_int_limits("long", __LONG_WIDTH__, LONG_MIN, LONG_MAX, ULONG_MAX);

	printf("float\n\tmin: %f\n\tmax: %f\n", FLT_MIN, FLT_MAX);
	printf("double\n\tmin: %f\n\tmax: %f\n", DBL_MIN, DBL_MAX);
	printf("long double:\n\tmin: %lf\n\tmax: %lf\n", LDBL_MIN, LDBL_MAX);
	
	return 0;
}
