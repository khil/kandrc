#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define SIZE 5
#define BUF_SIZE 100

char buf[BUF_SIZE]; /* buffer for ungetch */
int buf_p = 0;      /* next free position in buf */

/*
 * Exercise 5-1. As written, getint treats a + or - not followed by a didit as a 
 * valid representation of zero. Fix is to push a character back on the input.
 */

/* get a (possibly pushed back) character */
int getch() {
    return (buf_p > 0) ? buf[--buf_p] : getchar();
}

/* push a character back on input */
void ungetch(int c) {
    if (buf_p > BUF_SIZE)
        puts("unget_ch: too many characters\n");
    else
        buf[buf_p++] = c;
}

int getfloat(float *pn) {
    int c, sign, dec = -1;
    
    while (isspace(c = getch())) /* ignore whitespace */
        ;

    if (!isdigit(c) && c != EOF && c != '.' && c != '+' && c != '-') {
        ungetch(c);      /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            if (c != EOF)
                ungetch(c);
            ungetch((sign == 1) ? '+' : '-');
            return 0;
        }
    }
    for (*pn = 0; isdigit(c) || c == '.'; c = getch()) {
        if (c != '.') {
            *pn = 10 * *pn + (c - '0');
            if (dec >= 0)
                dec++;
        }
        else
            dec = 0;
    }
    *pn *= sign;
    if (dec > 0) /* move the decimal 'dec' places to the left */
        *pn /= pow(10, dec);
    if (c != EOF)
        ungetch(c);
    return c;
}


int main() {
    int n;
    float array[SIZE];

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        printf("%d -> %f\n", n+1, array[n]);

    return 0;
}

