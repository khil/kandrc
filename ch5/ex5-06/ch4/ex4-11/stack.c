#include <stdio.h>
#include "calc.h"

#define MAX_VAL 100   /* maximum depth of the val stack */

static int stack_p = 0;      /* next free stack position */
static double val[MAX_VAL];  /* value stack */

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

