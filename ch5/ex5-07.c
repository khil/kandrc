#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_LINES 5000
#define MAX_LEN 1000

/*
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the
 * program?
 */

int32_t _getline(char *line, int32_t maxlen) {
    int32_t c;
    char *s = line;

    while ((line - s) < (maxlen - 1) && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }

    if (c == EOF) {
        return EOF;
    }

    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';

    return s - line;
}


int32_t read_lines(char *lines[], char *line_buf, int32_t max_lines) {
    int32_t len, lines_read = 0;
    char *p = line_buf;

    while (lines_read < max_lines) {
        if ((len = _getline(p, MAX_LEN)) <= 0) {
            break;
        }
        p[len - 1] = 0;
        lines[lines_read++] = p;
        p += len;
    }

    return (lines_read <= max_lines) ? lines_read : -1;
}


void write_lines(char *lines[], int lines_cnt) {
    while (lines_cnt-- > 0) {
        puts(*lines++);
    }
}


void qsort(char *line_ptr[], int32_t left, int32_t right) {
    int32_t i, last;
    void swap(char *line_ptr[], int32_t i, int32_t j);

    if (left >= right) { /* do nothing if array contains */
        return;
    }
    /* fewer than two elements */
    swap(line_ptr, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (strcmp(line_ptr[i], line_ptr[left]) < 0) {
            swap(line_ptr, ++last, i);
        }
    }
    swap(line_ptr, left, last);
    qsort(line_ptr, left, last-1);
}


int32_t main() {
    int32_t nlines;
    char *line_ptr[MAX_LINES];
    char line_buf[MAX_LINES * MAX_LEN];

    if ((nlines = read_lines(line_ptr, line_buf, MAX_LINES)) >= 0) {
        qsort(line_ptr, 0, nlines - 1);
        write_lines(line_ptr, nlines);
        return 0;
    }
    else {
        puts("error: input too big to sort");
        return 1;
    }

    return 0;
}


void swap(char *line_ptr[], int32_t i, int32_t j) {
    char *temp = line_ptr[i];
    line_ptr[i] = line_ptr[j];
    line_ptr[j] = temp;
}

