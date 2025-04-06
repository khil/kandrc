#include <stdio.h>
#include <ctype.h>

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

int getint( int *pn) {
    int c, sign;
    
    while (isspace(c = getch())) /* ignore whitespace */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);      /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            if (c != EOF)
                ungetch(c);
            ungetch((sign == 1) ? '+' : '-');
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}


int main() {
    int n, array[SIZE];

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        printf("%d -> %d\n", n+1, array[n]);

    return 0;
}
