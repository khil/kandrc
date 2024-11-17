#include <stdio.h>
#include <math.h>
#include <ctype.h>

/*
** Exercise 4.3. Write a function htoi(s, which converts a string of hexadecimal
** digits (including an optional 0x or 0X) into its equivalent integer value.
** The allowable digits are 0 through 9 and a thorugh f and A through F.
**
** compile with -lm switch for the pow function
*/
#define TRUE 1
#define FALSE 0
#define MAXLEN 20

int getval(char prompt[], char line[], int max);
int hex_v(const char c); 
int starts_with(const char line[], const char test[]);
long htoi(const char line[], int len);


int main() {
	char val[MAXLEN];
	int len;

	while (len = getval("> ", val, MAXLEN))
		if (starts_with(val, "0"))
			printf("   %s = %ld\n", val, htoi(val, len));
		else
			printf("   0x%s = %ld\n", val, htoi(val, len));

	return 0;
}

int hex_v(const char c) {
	if isdigit(c)
		return c - 48;
	else if (c >= 65 && c <= 70)
		return c - 55;
	else if (c >= 97 && c <= 102)
		return c - 87;
	else
		return 0;
}

int starts_with(const char line[], const char test[]) {
	for(int i = 0; TRUE; i++) {
		if (test[i] == 0)
			return TRUE;
		else if (line[i] == 0 || line[i] != test[i])
			return FALSE;
	}
	return TRUE;
}

long htoi(const char s[], int len) {
	long num = 0;
	
	int p = (starts_with(s, "0x") || starts_with(s, "0X")) ? 2 : 0;
	for (int i = p; s[i]; i++)
		num = num + (hex_v(s[i]) * pow(16, (len - p) - (i - p) - 1));

	return num;
}

int getval(char prompt[], char line[], int max) {
	int c, i = 0;

	printf("%s", prompt);
	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;
	
	line[i] = '\0';

	return i;
}
