#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * Exercise 5-10. Write the program expr, which expruates a reverse Polish expression from the
 * command line, where each operator or operand is a separate argument. For example,
 * 
 *     expr 2 3 4 + *
 * expruates 2 * (3+4).
 */ 


#define ERROR 1
#define MAXPARMS 10
#define CHARACTER 0
#define OPERATOR 1
#define NUMBER 2


float expr(const float n1, const float n2, const char op) {
    switch (op) {
        case '+':
            return n1 + n2;
        case '-':
            return n1 - n2;
        case '*':
            return n1 * n2;
        case '/':
            return n1 / n2;
        case '%':
            return (int)n1 % (int)n2;
    }
    return 0;
}


uint8_t gettype(char *str) {
    char *p = str;
    
    if (strlen(p) == 1) {
        if (isdigit(*p))
            return NUMBER;
        return (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '%');
    }
    else {
        if (*p == '-' || *p == '+')
            p++;

        for(; *p; p++)
            if (!isdigit(*p) && *p != '.')
                return CHARACTER;

        return NUMBER;
    }
}


int32_t main(int32_t argc, char **argv) {
    if (argc < 3) {
        puts("insufficient parameters");
        return ERROR;
    }

    char **p, **p_op = NULL;
    for (p = argv+1; *p; p++) {
        switch(gettype(*p)) {
            case NUMBER:
                if (p_op) {
                    puts("The values must appear before operators.");
                    return ERROR;
                }
                break;
            case OPERATOR:
                if (!p_op)
                    p_op = p;
                break;
            default:
                puts("Invalid parameter.");
                return ERROR;
        }
    }

    if (!p_op) {
        puts("No operator argument.");
        return ERROR;
    }

    char **p_end = argv+(argc-1);
    if ((p_op - (argv+1)) - ((p_end - p_op) + 1) != 1) {
        puts("the must be one less operator than value.");
        return ERROR;
    }

    p = p_end;
    float result;
    for(char **p_nbr = p_op-1; p_nbr != argv && p != p_op-1; p_nbr--, p--) {
        if (p == p_end) {
            result = atof(*p_nbr);
            p_nbr--;
        }
        result = expr(atof(*p_nbr), result, *p[0]);
    }

    float f = result - (int)result;
    if (f >= 0.00001 || f <= -0.0001)
        printf(">> %.3f\n", result);
    else
        printf(">> %d\n", (int) result);

    return 0;
}

