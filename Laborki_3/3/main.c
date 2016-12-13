#include "head.h"
#include <stdio.h>

int main(void)
{
	for (int i = 1; i < 20; i++)
		printf("phi(%d) = %d\n", i, phi(i));
	
	return 0;
}