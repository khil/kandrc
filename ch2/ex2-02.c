#include <stdio.h>

/*
** Exercise 4.2.  Write a loop equivalent to the for loop above (getline)
** without using && or ||.
*/
#define TRUE 1
#define FALSE 0
#define MAXLINE 1000


int _getline(char line[], int max);


int main() {
	char line[MAXLINE];
	int len;

	len = _getline(line, MAXLINE);
	printf("%s", line);

	return 0;
}


int _getline(char line[], int max) {
	int c, more = TRUE, i = 0;

	// original
	//for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
	//	line[i] = c;
	
	while (more)
		if (i < (max - 1))
			if ((c = getchar()) != EOF)
				if (c != '\n')
					line[i++] = c;
				else
					more = FALSE;
			else
				more = FALSE;

	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}
