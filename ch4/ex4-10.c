#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Exercise 4-10. An alternate organization uses getline to read an entire input
 * line; this makes getch and ungetch unnessary. Revise the calculator to use
 * this approach.
 */

#define MAX_OP 100
#define MAX_VARS 27
#define NUMBER '0'
#define COMMAND '!'
#define SPECIAL_OP '&'
#define VAR_ASSGN 'V'
#define VAR_OFFSET 64
#define VAR_REF 'v'

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

    while ((type = get_op(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case VAR_REF:
                result = vars[toupper(s[0]) - VAR_OFFSET];
                if (result != DBL_MIN)
                    push(result);
                else
                    printf("error: variable '%c' is undefined\n", s[0]);
                break;
            case VAR_ASSGN:
                result = atof(s+2);
                if (result != DBL_MIN)
                    vars[toupper(s[0]) - VAR_OFFSET] = result;
                else
                    printf("error: %f cannot be assigned\n", DBL_MIN);
                break;
            case COMMAND:
                proc_cmd(s[0]);
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
                printf(">>> %.8g\n", vars[0]);
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
        case 'D':       /* command !D : dump all values on the stack */
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
#define BUF_SIZE 1000
char buf[BUF_SIZE];
char *buf_tok = NULL;
bool buf_nl = false;


int is_sign(char c) {
    return (c == '+' || c == '-');
}


int _getline(char line[], int max) {
	int c, i;

	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;

	if (c == EOF)
	   return EOF;
	else if (c == '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}


int get_op(char s[]) {
    int c, type = 0;

    if(!buf_tok) {              /* No token, read a line for stdin */
        if (buf_nl) {           /* send new line */
            buf_nl = false;
            return '\n';
        }
        printf("> ");
        int len = _getline(buf, BUF_SIZE);
        if (len == EOF)
            return EOF;
        else if (len == 1)
            return '\n';
        else
            buf_tok = strtok(buf, " ");
    }

    c = buf_tok[0];
    if (!isdigit(c) && !is_sign(c) && !isalpha(c) && c != '!' && c != '@') {
        type = c;                                          /* not a number */
        buf_nl = true;
    }
    else {
        if (c == '!') {                                   /* command or reference */
            strcpy(s, buf_tok+1);
            type = c;
        }
        else if (c == '@') {                              /* reference the most recent result */
            strcpy(s, buf_tok);
            type = VAR_REF;
        }
        else if (isalpha(c)) {                            /* var assignment, reference, or a special operator */
            strcpy(s, buf_tok);
            if (strlen(buf_tok) == 1)
                type = VAR_REF;
            else if (buf_tok[1] == '=')
                type = VAR_ASSGN;
            else {
                type = SPECIAL_OP;
                buf_nl = true;
            }
        }
        else if (is_sign(c) && strlen(buf_tok) == 1) {    /* sign operations */
            type = buf_tok[0];
            buf_nl = true;
        }
        else {
            strcpy(s, buf_tok);
            type = NUMBER;
        }
    }

    // get the next token from buf
    buf_tok = strtok(NULL, " \n");
    return type;
}
