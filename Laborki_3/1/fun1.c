#include "head.h"
#include <string.h>

bool palindrom(char *napis)
{
	for (int i = 0, j = strlen(napis) - 1; i < j; i++, j--)
		if (napis[i] != napis[j])
			return false;
	return true;
}