#include "agents.h"
#include <math.h>

double distance(struct agent ob1, struct agent ob2)
{
	double x = ob1.x - ob2.x;
	double y = ob1.y - ob2.y;
	return sqrt(x*x + y*y);
}