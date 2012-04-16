#include <iostream>
#include "world.hpp"

#if defined(__linux__) || defined(__APPLE__)
	#include <time.h>
#elif defined(_WIN32) || defined(_WIN64)
	#include <Windows.h>
#else
	#error("Target Operating System not recognized")
#endif


double 	World::time0 = 0.0,
	World::deltaFreeze = 0.0,
	World::lastFreezeStart = 0.0;
bool 	World::freezed = false;

#if defined(_WIN32) || defined(_WIN64)
    double World::freq = 0.0;
#endif

World::World(void)
{
	if(time0==0.0)
	{
		#if defined(__linux__) || defined(__APPLE__)
			timespec time_0;
			clock_gettime(CLOCK_REALTIME, &time_0);
			time0 = time_0.tv_sec + time_0.tv_nsec/1e9;
		#elif defined(_WIN32) || defined(_WIN64)
			LARGE_INTEGER li;
			QueryPerformanceFrequency(&li);
			freq = double(li.QuadPart);
			QueryPerformanceCounter(&li);
			time0 = static_cast<double>(li.QuadPart)/freq;
		#endif
	}
}

World::~World(void)
{ }

double World::getTime(bool raw)
{
	double tm = 0.0;

	#if defined(__linux__) || defined(__APPLE__)
		timespec time1;
		clock_gettime(CLOCK_REALTIME, &time1);
		tm = time1.tv_sec + time1.tv_nsec/1e9 - time0;
	#elif defined(_WIN32) || defined(_WIN64)
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		tm = static_cast<double>(li.QuadPart)/freq - time0;
	#endif

	if(raw)
		return tm;
	if(!freezed)
		return tm - deltaFreeze;
	else
		return lastFreezeStart - deltaFreeze;
}

void World::freeze(void)
{
	if(!freezed)
	{
		lastFreezeStart = getTime(true);
		freezed = true;
		std::cout << "Freezed at " << lastFreezeStart << " second(s)" << std::endl;
	}
}

void World::unfreeze(void)
{
	if(freezed)
	{
		deltaFreeze += getTime(true) - lastFreezeStart;
		std::cout << "Paused " << getTime(true) - lastFreezeStart << " second(s)" << std::endl;
		freezed = false;
	}
}

bool World::isFreezed(void)
{
	return freezed;
}

void World::switchFreeze(void)
{
	if(freezed)
		unfreeze();
	else
		freeze();
}
