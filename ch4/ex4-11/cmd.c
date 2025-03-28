#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

extern double vars[MAX_VARS];

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
