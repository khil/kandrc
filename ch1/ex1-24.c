#include <stdio.h>

/*
 * Exercise 1-24. Write a program to check a C program for rudimentary syntax
 * errors like unbalanced parentheses, brackets, and braces.  Don't forget about
 * quotes, both single and double, escape sequences, and comments.  (this pro-
 * gram is hard if you do in in full generality.)
*/

#define MAXLINE 1000
#define TRUE 1
#define FALSE 0
#define COUNTERS 4
#define LINE_ERRORS 3


int _getline(char line[], int maxline);
int is_valid_syntax(char line[], int len, int counters[], int line_error[]);


int main() {
	int i, len, n, line_errors[LINE_ERRORS], counters[COUNTERS];
	char line[MAXLINE];
	int errors = 0;

	for (i = 0; i < COUNTERS; i++)
		counters[i] = 0;

	for (i = 0; i < LINE_ERRORS; i++)
		line_errors[i] = 0;

	/* 
	 * Read each line, then check it for syntax errors; inline errors will be caught and output
	 * with the error message below the offending line; Errors that may span multiple lines
	 * cannot be determined immediately and output once the entire input file is processed.
	*/
	for (n = 1; ((len = _getline(line, MAXLINE)) > 0); n++) {
		if (is_valid_syntax(line, len, counters, line_errors) == FALSE) {
			printf("%sSYNTAX ERROR -> ", line);
			if (line_errors[0] > 0) {
				printf("unclosed single quote on line %d, starting at position %d.\n", n, line_errors[0]);
				errors++;
			}
			if (line_errors[1] > 0) {
				printf("unclosed double quote on line %d, starting at position %d.\n", n, line_errors[1]);
				errors++;
			}
			if (line_errors[2] > 0) {
				printf("unknown escape sequence on line %d, at position %d.\n", n, line_errors[2]);
				errors++;
			}
			for (i = 0; i < LINE_ERRORS; i++)
				line_errors[i] = 0;
		}
	}

	if (counters[0] > 0) {
		printf("SYNTAX ERROR -> unclosed c-89 comment!\n");
		errors++;
	}
	if (counters[1] > 0) {
		printf("SYNTAX ERROR -> unmatched bracket!\n");
		errors++;
	}
	if (counters[2] > 0) {
		printf("SYNTAX ERROR -> unmatched parenthesis!\n");
		errors++;
	}
	if (counters[3] > 0) {
		printf("SYNTAX ERROR -> unmatched bracket!\n");
		errors++;
	}

	if (errors > 0)
		printf("\n\t>>> Syntax Check Failed:  %d errors found! <<<\n", errors);
	else
		printf("\n\t>>> Syntax Check Successful! <<<\n");

	return 0;
}


int is_valid_syntax(char line[], int len, int counters[], int line_error[]) {
	/*
	** Basic C code syntax checker; returns false if the line fails the check and the line_errors
	**		array will hold the position of the failed open quote of invalid escape sequence.
	**      A counter array are used any syntax features that can span multiple lines.
	**
	**		counters (4 elements): when any of these values are > 0 you have unmatched syntax elements
	**			0: multiline C89 style comments
	**			1: braces
	**			2: parenthesis
	**			3: brackets
	**
	**		line_errors (3 elements):
	**			0: single quotes
	**			1: double quotes
	**			2: escape sequences
	**
	** Checks for:
	**	- Unclosed brackets, parentheses, and braces, and C-89 comments across multiple lines
	**		* because these types can span multiple lines the counters array keeps track
	**			of matching. All counters equal zero after processing all the lines, a non-zero
	**			in one of the nodes indicates a failed match.
	**	- Unclosed quotes (both single and double) on a single line -> returns false
	**	- Invalid escape sequences on a single line -> returns false
	*/
	char c, last_c;
	int i, in_comment, in_sgl_quote, in_dbl_quote;
	int return_code = TRUE;

	in_sgl_quote = in_dbl_quote = FALSE;
	in_comment = (counters[0] > 0);

	for (i = 0; i < len; i++) {
		c = line[i];
		if (in_comment == TRUE) {
			if (c == '/' && last_c == '*') {
				in_comment = FALSE;	     /* end inline C89 style comment */
				counters[0]--;
			}
		} else if (in_sgl_quote > 0 || in_dbl_quote > 0) {
			if (last_c == '\\') {
				if (c == 'n' || c == '0' || c == 't' || c == 'b' || c == '\\' || c == '\'')  // escape sequences
					;	
				else {
					line_error[2] = i + 1;
					return_code = FALSE;
				}
			}

			if (in_sgl_quote > 0 && c == '\'') {
				if ((last_c != '\\') || (last_c == '\\' && i > 2 && line[i-2] != '\''))
					in_sgl_quote = FALSE;
			} else if (in_dbl_quote > 0 && c == '"') {
				in_dbl_quote = FALSE;
			}
		} else {
			if (c == '*' && last_c == '/') {			/* begin C89 style comment */
				counters[0]++;
				in_comment = TRUE;
			} else if (c == '/' && last_c == '/') {		//  inline C99 style comment
				i = len;								/* everything after this point is irrelevant */
			} else if (c == '{') {
				counters[1]++;
			} else if (c == '}') {
				counters[1]--;
			} else if (c == '(') {
				counters[2]++;
			} else if (c == ')') {
				counters[2]--;
			} else if (c == '[') {
				counters[3]++;
			} else if (c == ']') {
				counters[3]--;
			} else if (c == '\'' && last_c != '\\') {
				in_sgl_quote = i + 1;
			} else if (c == '"') {
				in_dbl_quote = i + 1;
			}
		}
		last_c = c;
	}

	if (in_sgl_quote > 0) {
		line_error[0] = in_sgl_quote;
		return_code = FALSE;
	} else if (in_dbl_quote > 0) {
		line_error[1] = in_dbl_quote;
		return_code = FALSE;
	}

	return return_code;
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
