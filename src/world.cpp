#include "world.hpp"
#include <ctime>


double World::time0 = 0;

World::World(void)
{ }


double World::setTime(double t)
{
	return time0 = t;
}

double World::getTime(void)
{
	return 1000 * clock()/CLOCKS_PER_SEC  - time0;
}

