#include <stdio.h>

/*
 * Exercise 1-17. Write a program to print all input lines that are longer than 80
 * characters.
*/

#define MAXLINE 1000

int _getline(char line[], int maxline); /* used _getline because getline is a already defined in stdio */
int _putline(char line[], int len);

int main() {
	int len, max, i;
	char line[MAXLINE];

	while ((len = _getline(line, MAXLINE)) > 0) {
		if (len > 80) {
			_putline(line, len);
		}
	}

	return 0;
}


int _getline(char line[], int maxline) {
	int c, i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;

	if (c == '\n') {
		line[i] = c;
		i++;
	}

	line[i] = '\0';

	return i;
}

int _putline(char line[], int len) {
	int i;
	
	for (i = 0; i <= len && line[i] != '\0'; i++) {
		putchar(line[i]);
	}

	return i;
}
