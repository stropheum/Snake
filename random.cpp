#include <stdlib.h>

#include "random.h"
float getRangedRandom(float min, float max)
{
	auto r = rand();

	auto r1 = float(r) / float(RAND_MAX);
	r1 *= (max - min);
	r1 += min;

	return r1;
}

int getRangedRandom(int min, int max)
{
	auto r = rand();

	auto r2 = float(r) / float(RAND_MAX);
	r2 *= (float(max) - float(min));
	auto r1 = int(r2);
	r1 += min;

	return r1;

}