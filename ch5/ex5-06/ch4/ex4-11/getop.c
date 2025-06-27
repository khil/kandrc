#include <stdio.h>
#include <ctype.h>
#include "calc.h"
#include <stdio.h>

/* didn't use an internal static variable because unget_ch was referenced in multiple
 * functions. So I used an external static variable with the _getch wrapper function
 * to handle the new getch functionality and minimize code revisions.
 */

static int unbuf = EOF;

int _getch() {
    if (unbuf != EOF) {
        int ch = unbuf;
        unbuf = EOF;
        return ch;
    }
    else 
        return get_ch();
}

int is_sign(char c) {
    return (c == '+' || c == '-');
}

int get_number(char c, char *s) {
    char *p = s;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(*++p = c = _getch()))
            ;

    if (c == '.')   /* collect fraction part */
        while (isdigit(*++p = c = _getch()))
            ;

    *p = '\0';

    if (c != EOF && c != '\n') {
        unbuf = c;
        return 0;
    }
    else
        return c;
}

int get_op(char *s) {
    int c;
    char *p = s;

    /* ignore white space */
    while ((*p = c = _getch()) == ' ' || c == '\t')
        ;
    *(p + 1) = '\0';

    if (!isdigit(c) && !is_sign(c) && !isalpha(c) && c != '.' && c != '!' && c != '@')
        return c;   /* not a number */

    if (c == '@') {                           /* Reference the last result variable */
        c = _getch();
        return VAR_REF;
    }

    if (c == '!') {                         /* handle command leader */
        while (isalpha(*p++ = c = _getch()))
            ;
        *p = '\0';
        return COMMAND;
    }

    if (isalpha(c)) {                        /* handle (possible) variable assignment or reference */
        int prev_c = c;
        *++p = c = _getch();
        if (c == '=') {                      /* Assignment */
            *++p = c = _getch();
            if (isdigit(c)) {
                get_number(c, p);
                return VAR_ASSGN; 
            }
            else
                unbuf = c;
        }
        else if (c == ' ' || c == '\n') {    /* reference */ 
            if (c == ' ')
                unbuf = c;
            return VAR_REF;
        }
        else {
            /* not a variable - reset */
            unbuf = c;
            p--;
            c = prev_c;
        }
    }

    if (c == 's' || c == 'e' || c == 'p') {  /* handle special operator (sin, exp, pow) */
        while (isalpha(*++p = c = _getch()))
            ;
        *p = 0;
        if (c != EOF)
            unbuf = c;
        return SPECIAL_OP;
    }

    if (is_sign(c)) {                        /* handle sign operations and signed numbers */
        int sign = c;
        *++p = c = _getch();
        if (!isdigit(c)) {                   /* the sign was not followed by a number, */ 
            unbuf = c;
            *p = '\0';
            return sign;
        }
    }

    if (isdigit(c)) {
        get_number(c, p);
        return NUMBER;
    }
    
    if (c != EOF)
        unbuf = c;
    return c;
}

