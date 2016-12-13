#include "head.h"

long int nwd(long int a, long int b)
{
	// a jest wieksze od b
	long int r;
	while (r = a % b)
	{
		a = b;
		b = r;
	}
	return b;
}