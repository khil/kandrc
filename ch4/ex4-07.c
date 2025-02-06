#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Exercise 4-7. Write a routine ungets(s) that will push back the entire
 * string onto the input. Should ungets know about buf and bugf, or should
 * it just use ungetch?
 */

#define MAX_OP 100
#define MAX_VARS 27
#define NUMBER '0'
#define COMMAND '!'
#define SPECIAL_OP '&'
#define VAR_ASSGN 'V'
#define VAR_OFFSET 64
#define VAR_REF 'v'
#define LAST_OUT '$'

void push(double f);
double pop();
int get_op(char []);
void proc_cmd(char c);

double vars[MAX_VARS];


/* reverse Polish calculator */
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
                result = atof(s+1);
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

/*****************************************************************************/

void peek();
void clear();
void duplicate();
void swap();
void dump();

void proc_cmd(char c) { 
    switch (c) {
        case 'c':       /* command !c : clear the stack */
            clear();
            break;
        case 'd':       /* command !d : duplicate first item on stack */
            duplicate();
            break;
        case 'D':       /* command !D : dump all values on ths stack */
            dump();
            break;
        case 'p':       /* command !p : display the first item on the stack */
            peek();
            break;
        case 's':       /* command !s : swap the first two items on the stack */
            swap();
            break;
        case 'v':       /* command !v : dump all stored names variables */
            puts("! vars: ");
            for (int i = 0; i < MAX_VARS; i++)
                if (vars[i] != DBL_MIN)
                    printf("\t%c = %f\n", i + VAR_OFFSET, vars[i]);
            break;
        case 'x':       /* command !x : exit the program */
            exit(0);
        default:
            puts("error: invalid command");
            break;
    }
}

/*****************************************************************************/

#define MAX_VAL 100   /* maximum depth of the val stack */

int stack_p = 0;      /* next free stack position */
double val[MAX_VAL];  /* value stack */

/* Dump the entire stack */
void dump() {
    printf("! (%d) ", stack_p);
    for (int i = 0; i < stack_p; i++)
        printf("%f; ", val[i]);
    puts("");
}

/* clear the stack */
void clear() {
    stack_p = 0;
    puts("! stack cleared");
}

/* duplicate the first item in the queue */
void duplicate() {
    if (stack_p == 1) {
        val[stack_p++] = val[0];
        puts("! duplicated");
    }
    else
        puts("! error: can't duplicate");
}

/* swap the first two elements of that stack */
void swap() {
    if (stack_p >= 2) {
        double t = val[1];
        val[1] = val[0];
        val[0] = t;
        puts("! swapped");
    }
    else
        puts("! error: insufficient items to swap");
}

/* display the top element of the stack */
void peek() {
    if (stack_p > 0) {
        printf("> %f\n", val[stack_p-1]);
    }
    else
        puts("> -");
}

/* push: push f onto the value stack */
void push(double f) {
    if (stack_p < MAX_VAL) {
        val[stack_p++] = f;
    }
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

int is_sign(char c) {
    return (c == '+' || c == '-');
}

int get_number(char c, int i, char s[]) {
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = get_ch()))
            ;

    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = get_ch()))
            ;

    s[i] = '\0';

    if (c != EOF && c != '\n') {
        unget_ch(c);
        return 0;
    }
    else
        return c;
}

/* get_op: get next operator or numeric operand */
int get_op(char s[]) {
    int i, c;

    /* ignore white space */
    while ((s[0] = c = get_ch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && !is_sign(c) && !isalpha(c) && c != '.' && c != '!' && c != '@')
        return c;   /* not a number */

    i = 0;
    if (c == '@') {                           /* Reference the last result variable */
        c = get_ch();
        return VAR_REF;
    }

    if (c == '!') {                         /* handle command leader */
        while (isalpha(s[i++] = c = get_ch()))
            ;
        s[i] = '\0';
        return COMMAND;
    }

    if (isalpha(c)) {                        /* handle (possible) variable assignment or reference */
        int prev_c = c;
        c = get_ch();
        if (c == '=') {                      /* Assignment */
            s[++i] = c = get_ch();
            if (isdigit(c)) {
                get_number(c, i, s);
                return VAR_ASSGN; 
            }
            else
                unget_ch(c);
        }
        else if (c == ' ' || c == '\n') {    /* reference */ 
            if (c == ' ')
                unget_ch(c);
            return VAR_REF;
        }
        else {
            /* not a variable - reset */
            unget_ch(c);
            c = prev_c;
        }
    }

    if (c == 's' || c == 'e' || c == 'p') {  /* handle special operator (sin, exp, pow) */
        while (isalpha(s[++i] = c = get_ch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            unget_ch(c);
        return SPECIAL_OP;
    }

    if (is_sign(c)) {                        /* handle sign operations and signed numbers */
        int sign = c;
        s[++i] = c = get_ch();
        if (!isdigit(c)) {                   /* the sign was not followed by a number, */ 
            unget_ch(c);                     /* treat it as an operation */
            s[i] = '\0';
            return sign;
        }
    }

    if (isdigit(c)) {
        get_number(c, i, s);
        return NUMBER;
    }
    
    if (c != EOF)
        unget_ch(c);
    return c;
}

/*****************************************************************************/

/* push a string of characters back on input */
void ungets(char str[]) {
    /*
     * The function ungets could use or know about buf and bufp directly, but
     * it is completely unnecessary. The only benefit would be not writing
     * repeated error messages in the event pushing the str back into buf would
     * exceedng BUF_SIZE and that could be rectified by returning a non-zero
     * when that occurs, and of course adding a check in this function.
     */  
    for (int i = 0; str[i] != 0; i++)
        unget_ch(str[i]);
}

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
        buf[buf_p++] = c;
}


