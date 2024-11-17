#include <stdio.h>

/*
** Exercise 2-4.  Wrtie an alternate version of sqeeze(s1, s2) that deletes
** each character is s2 that matches any character in the string s2.
*/

#define MAXLEN 1000

int _getline(char line[], int max);
void squeeze(char s1[], const char s2[]);


int main() {
	char line[MAXLEN];
	int len;

	while ((len = _getline(line, MAXLEN)) > 1) {
		printf("before: %s", line);
		squeeze(line, "abc");
		printf(" after: %s", line);
	}
	return 0;
}


void squeeze(char s1[], const char s2[]) {
	int i, j, k;

	for(i = 0; s2[i]; i++) {
		for (j = 0; s1[j]; j++) {
			if (s1[j] == s2[i]) {
				for (k = j; s1[k]; k++)
					s1[k] = s1[k+1];
				s1[k] = 0;
			}
		}
	}
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
