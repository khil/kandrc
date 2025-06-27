#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

#define MAX_OP 100

/*
 * Exercise 5-6. Rewrite the appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.  Good possibilities include getline
 * (Chapters 1 and 4), itoa, and their variants (Chapters 2, 3, and 4).
 * reverse (chapter 3), and strindex and getop (chapter 4).
 *
 *
 * rewrite of exercise 4-11. Modify getop so that it doesn't need to use
 * ungetch. Hint: use an internal static variable
 *
 * See goeop.c cor updates
 */

double vars[MAX_VARS];

int main() {
    int type;
    double op2, result;
    char s[MAX_OP];
    /* initialize vars; */
    for (int i = 0; i < MAX_VARS; i++)
        vars[i] = DBL_MIN;

    printf("> ");
    while ((type = get_op(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                printf("> ");
                break;
            case VAR_REF:
                result = vars[toupper(s[0]) - VAR_OFFSET];
                if (result != DBL_MIN)
                    push(result);
                else
                    printf("error: variable '%c' is undefined\n", s[0]);
                printf("> ");
                break;
            case VAR_ASSGN: 
                result = atof(s+2);
                if (result != DBL_MIN)
                    vars[toupper(s[0]) - VAR_OFFSET] = result;
                else
                    printf("error: %f cannot be assigned\n", DBL_MIN);
                printf("> ");
                break;
            case COMMAND:
                proc_cmd(s[0]);
                printf("> ");
                break;
            case SPECIAL_OP:
                if (!strncmp(s, "sin", 3))
                    push(sin(pop()));
                else if (!strncmp(s, "exp", 3))
                    push(exp(pop()));
                else if (!strncmp(s, "pow", 3)) {
                    op2 = pop();
                    push(pow(pop(), op2));
                }
                else
                    puts("error: unknown special operator");
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    puts("error: zero divisor");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push((int) pop() % (int) op2);
                else
                    puts("error: zero divisor");
                break;
            case '\n':
                vars[0] = pop();
                printf(">>> %.8g\n> ", vars[0]);
                break;
            default:
                printf("error: unknown command (%s)\n", s);
                break;
        }
    }
    puts("\b\babort");
    
    return 0;
}

