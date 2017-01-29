#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
bool match(char *pattern, char *text);

int main(void)
{
	char t1[100], t2[100];
	
	while (true)
	{
		printf("Wzorzec: ");
		gets(t1);
		printf("Tekst: ");
		gets(t2);
		
		printf("Wynik: %d\n", match(t1, t2));
		if (t1[0] == '\0' && t2[0] == '\0')
			break;
	}
	return 0;
}

bool match(char *pattern, char *text)
{	
	if (*pattern == '\0')
		return (*text == '\0') ? true : false;
	
	if (*pattern == '?')
		return (*text == '\0') ? false : match(pattern + 1, text + 1);
	if (*pattern == '*')
	{
		while (*(++pattern) == '*');
		do
		{
			if (match(pattern, text))
				return true;
		} while (*text++ != '\0');
		return false;
	}
	return (*pattern == *text && *text != '\0') ? match(pattern + 1, text + 1) : false;
}