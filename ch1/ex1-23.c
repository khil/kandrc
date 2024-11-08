#include <stdio.h>

/*
 * Exercise 1-23. Write a program to remove all comments for a C program.
 * Don't forget to handle quoted string and character constants properly. C com-
 * ments do not nest.
*/

#define MAXLINE 1000
#define TRUE 1
#define FALSE 0


int _getline(char line[], int maxline);
int _remove(char str[], int len, int start_i, int end_i); 
int strip_comments(char line[], int len, char multi_line[]);


int main() {
	int len;
	char line[MAXLINE];
	char multi_line_comment[1];
	multi_line_comment[0] = FALSE;

	while ((len = _getline(line, MAXLINE)) > 0) {
		len = strip_comments(line, len, multi_line_comment);
		if (len > 0)
			printf("%s", line);
	}

	return 0;
}


int _remove(char str[], int len, int start_i, int end_i) {
	/*
	** Remove a portion of the character array starting at start_i, ending at
	** end_i, returning the new length of the array.
	*/
	if (len > 0 && start_i < end_i) {
		if (end_i < len) {
			// remove a portion of the string
			int i, j;
			for (i = start_i, j = end_i; i < len; i++, j++)
				str[i] = str[j];
			len = len - (end_i - start_i);
		}
		else {
			// truncate the array
			if (start_i > 0) {
				str[start_i++] = '\n';
				str[start_i++] = '\0';
			}
			else
				str[0] = '\0';  // nothing left in the array

			len = start_i;
		}
	}

	return len;
}


int strip_comments(char line[], int len, char multi_line[]) {
	/*
	** Strip comments from the line (char array) and print it to the stdout.
	** The multi_line array parm should only contain one boolean element. When
	** TRUE, the previous line started a block comment. This value will be set
	** as appropriate (this is a work-around to return an multi-line comment 
	** indicator; we havn't learned pointers or structs yet). Returns the 
	** length of the line.
	*/
	int i, c, last_c = ' ';
	int start_comment, end_comment = -1;
	int cont_i = 0;

	if (multi_line[0] > 0)
		start_comment = 0;
	else
		start_comment = -1;

	do {
		for (i = cont_i; i < len; i++) {
			c = line[i];
			if (start_comment >= 0) {
				if (last_c == '*' && c == '/') {
					end_comment = i + 1;	 /* end inline C89 style comment */
					i = len;				 /* break out of loop */
				}
			}
			else if (last_c == '/') {
				if (c == '*') {				/* begin C89 style comment */
					start_comment = i - 1;
				} else if (c == '/') {		// begin & end inline C99 style comment
					start_comment = i - 1;
					end_comment = len - 1;
					i = len;				 /* break out of loop */
				}
			}
			last_c = c;
		}

		if (start_comment >= 0) {
			if (end_comment > 0) {
				// delete everything between start_comment and end_comment
				len = _remove(line, len, start_comment, end_comment);
				start_comment = end_comment = -1;
				cont_i = end_comment;
				last_c = ' ';
				multi_line[0] = FALSE;
			} else {
				// delete until the end of the line
				len = _remove(line, len, start_comment, len);
				cont_i = len;
				multi_line[0] = TRUE;
			}
		}
		else
			cont_i = len;					/* line contains no comments */
	}
	while (cont_i < len);

	return len;
}


int _getline(char line[], int maxline) {
	int c, i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;

	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}
