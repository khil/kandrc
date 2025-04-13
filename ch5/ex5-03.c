#include <stdio.h>

/*
 * Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in chapter2: strcat(s,t) copies the string t to the end of s.
 */

void _strcat(char *s, char *t) {
    while (*s) 
        s++;
    while (*s++ = *t++)
        ;
}


int main() {

    char s[100] = "Hello";
    _strcat(s, ", world!");
    printf("s=%s\n", s);
    _strcat(s, " Goodbye.");
    printf("s=%s\n", s);
    return 0;
}

