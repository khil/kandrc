#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define ERROR 1
#define MAXPARMS 10

#define CHARACTER 0
#define OPERATOR 1
#define NUMBER 2


void gen_eq(char *s1, char *s2, char *op, char *res) {
    strcat(res, "(");
    strcat(res, s1);
    strcat(res, op);
    strcat(res, s2);
    strcat(res, ")"); 
}


uint8_t gettype(char *str) {
    char *p = str;

    if (strlen(p) == 1) {
        if (isdigit(*p))
            return NUMBER;
        return (*p == '+' || *p == '-' || *p == '*' || *p == '/');
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

    char **p, **p_op = NULL, **p_end = NULL;

    for (p = argv+1; *p; p++) {
        printf("%ld -> %s -> ", p - (argv+1), *p);
        switch(gettype(*p)) {
            case NUMBER:
                if (p_op) {
                    puts("Numbers must appear before operators.");
                    return ERROR;
                }
                puts("number");
                break;
            case OPERATOR:
                puts("operator");
                p_end = p;
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

    if (p_op - (argv+1) < 2) {
        puts("At least two numbers are required.");
        return ERROR;
    }

    printf("op: %ld\n", p_op - (argv+1));
    printf("end: %ld\n", p_end - (argv+1));

    char res[1024] = {0};
    for(char **p_nbr = p_op-1; p_nbr != argv && p_end != p_op; p_nbr-=2, p_op--) {
        gen_eq(*(p_nbr-1), *p_nbr, *p_end, res);
        puts(res);
    }

    puts(res);
    

    return 0;
}
