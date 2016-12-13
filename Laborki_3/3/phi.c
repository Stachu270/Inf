#include "head.h"

int phi(long int n)
{
	int count = 0;
	for (int i = 1; i <= n; i++)
	{
		if (nwd(n, i) == 1)
			count++;
	}
	return count;
}