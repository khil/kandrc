#include <assert.h>
#include <ctype.h>
#include <math.h>

/*
 * Extend atof to handle scientific notation of the form
 *     123.45-6
 * where a floating-point number may be follower by e or E or an optionally
 * signed exponent.
 */

int almost_eq(double x, double y, double eps) {
    return (x - y) <= eps;
}


double _atof(char s[]) {
    double val, power;
    int i, sign;

    for (i=0; isspace(s[i]); i++) /* skip leading whitespace */
        ;
    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    val = sign * val / power;

    /* handle scientific notation */
    if (tolower(s[i]) == 'e') {
        i++;
        sign = (s[i] == '-') ? -1 : 1;

        if (s[i] == '+' || s[i] == '-')
            i++;
        int n;
        for (n=0; isdigit(s[i]); i++)
            n = 10 * n + (s[i] - '0');

        val = val * pow(10, (n * sign));
    }

    return val;
}


int main() {
    assert(almost_eq(_atof("-7.56012"), -7.56, 0.00000001) == 1);

    assert(almost_eq(_atof("-7.56012"), -7.5601, 0.00000001) == 1);

    assert(almost_eq(_atof("7.56012"), 7.56012, 0.00000001) == 1);

    assert(almost_eq(_atof("7.5e-6"), 0.0000075, 0.00000001) == 1);
    
    assert(almost_eq(_atof("7.5E-6"), 0.0000075, 0.00000001) == 1);

    assert(almost_eq(_atof("7.5e+6"), 7500000, 0.000001) == 1);

    assert(almost_eq(_atof("7.5e6"), 7500000, 0.000001) == 1);

    return 0;
}

