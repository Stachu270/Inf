#include "zad1.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (palindrom(argv[i]))
			printf("\"%s\" jest palindromem\n", argv[i]);
		else
			printf("\"%s\" nie jest palindrom\n", argv[i]);
	}
	
	return 0;
}
