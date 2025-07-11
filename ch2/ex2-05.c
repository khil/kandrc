#include <stdio.h>
#include <limits.h>

/*
** Exercise 2-5.  Write an function any(s1, s2), which returns the first location
** in the string s1 where any character from the string s2 occurs, or -1 if s1
** contains no characters from s2. (The standard library function strpbrk does
** the same job but returns a pointer to the location.)
*/

#define MAXLEN 1000

int _getline(char line[], int max);
int any(const char s1[], const char s2[]);


int main() {
	char line[MAXLEN];
	int len;

	while ((len = _getline(line, MAXLEN)) > 1) {
		int res = any(line, "aeiou");
		printf("location of a, e, i, o, or u: %d\n", res);
	}
	return 0;
}


int any(const char s1[], const char s2[]) {
	int i, j, k;
    k = INT_MAX;

	for(i = 0; s2[i]; i++) {
		for (j = 0; s1[j]; j++) {
			if (s1[j] == s2[i])
                if (j < k)
                    k = j;
		}
	}

    if (k == INT_MAX)
        return -1;
    else
        return k;
}


int _getline(char line[], int max) {
	int c, i;

	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;
	
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}
