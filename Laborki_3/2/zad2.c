#include "zad2.h"
#include <math.h>
#include <stdlib.h>
double dabs(double x) {return (x > 0) ? x : -x; }

double f(double x)
{
	return cos(x/2);
}

double rozwiazanie(double a, double b, double eps)
{
	while (dabs(f(b) - f(a)) > eps)
	{
		if (f(b) * f((a + b) / 2) < 0)
			a = (a + b) / 2;
		else
			b = (a + b) / 2;
	}
	return (a + b)/2;
}