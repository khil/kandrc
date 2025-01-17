#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Exercise 4-3. Given the basic framework, it's straightforward to extend the
 * calculator. Add the modulus (%) operator and provisions for negative numbers.
 */

#define MAX_OP 100
#define NUMBER '0'

void push(double f);
double pop();
int get_op(char []);


/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAX_OP];

    while ((type = get_op(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
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
                    puts("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push((int) pop() % (int) op2);
                else
                    puts("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command (%s)\n", s);
                break;
        }
    }
    return 0;
}

/*****************************************************************************/

#define MAX_VAL 100   /* maximum depth of the val stack */

int stack_p = 0;     /* next free stack position */
double val[MAX_VAL];  /* value stack */


/* push: push f onto the value stack */
void push(double f) {
    if (stack_p < MAX_VAL)
        val[stack_p++] = f;
    else
        printf("error stack full, can't push (%g)\n", f);
}

/* pop: pop and return top value from the stack */
double pop() {
    if (stack_p > 0)
        return val[--stack_p];
    else {
        puts("error: stack empty\n");
        return 0.0;
    }
}

/*****************************************************************************/

int get_ch();
void unget_ch(int);

/* issign: return one when the argument is +/- otherwise zero */ 
int issign(char c) {
    if (c == '-' || c == '+')
        return 1;
    return 0;
}

/* get_op: get next operator or numeric operand */
int get_op(char s[]) {
    int i, c;

    while ((s[0] = c = get_ch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && !issign(c) && c != '.')
        return c;   /* not a number */
    i = 0;
    if (issign(c)) /* collect the sign */
        while (issign(s[++i] = c = get_ch()))
            ;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = get_ch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = get_ch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        unget_ch(c);

    return NUMBER;
}

/*****************************************************************************/

#define BUF_SIZE 100

char buf[BUF_SIZE]; /* buffer for ungetch */
int buf_p = 0;     /* next free position in buf */


/* get a (possibly pushed back) character */
int get_ch() {
    return (buf_p > 0) ? buf[--buf_p] : getchar();
}

/* push a character back on input */
void unget_ch(int c) {
    if (buf_p > BUF_SIZE)
        puts("unget_ch: too many characters\n");
    else
        buf[buf_p] = c;
}

