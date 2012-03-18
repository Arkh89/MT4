#include "world.hpp"

#if defined(__linux__) || defined(__APPLE__)
#include <time.h>
#elif defined(_WIN32) || defined(_WIN64)
#include<Windows.h>
#else
#error("Target Operating System not recognized")
#endif


double World::time0 = 0;

World::World(void)
{ }

World::~World(void)
{ }

double World::setTime(void)
{
	#if defined(__linux__) || defined(__APPLE__)
	timespec time_0;
	clock_gettime(CLOCK_REALTIME, &time_0);
	return time0 = 1000.0*time_0.tv_sec + time_0.tv_nsec/1000000.0;

	#elif defined(_WIN32) || defined(_WIN64)
	QueryPerformanceCounter((LARGE_INTEGER *)&time0);
	return 1000.0*(time0)/freq;

	#endif
}


double World::getTime(void)
{
	#if defined(__linux__) || defined(__APPLE__)
	timespec time1;
	clock_gettime(CLOCK_REALTIME, &time1);
	return 1000.0*time1.tv_sec + time1.tv_nsec/1000000.0- time0;

	#elif defined(_WIN32) || defined(_WIN64)
	double time,freq;
	QueryPerformanceCounter((LARGE_INTEGER *)&time);
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
	return 1000.0*(time - time0)/freq;

	#endif
}

