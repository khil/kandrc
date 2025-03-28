#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 100

static char buf[BUF_SIZE]; /* buffer for ungetch */
static int buf_p = 0;     /* next free position in buf */


void dump_buf() {
    printf("dumping 'buf' ->\n\t\"");
    for (int i = buf_p-1; i >= 0; i--)
        printf("%c0x%02x ", (buf[i] < 0 ? '-' : '\0'), abs(buf[i]));
    printf("\b\"\n");
}

/* get a (possibly pushed back) character */
int get_ch() {
    return (buf_p > 0) ? buf[--buf_p] : getchar();
}

