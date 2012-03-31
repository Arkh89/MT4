#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED
#include<ctime>

using namespace std;


class World
{
	public:

		World(void);
		~World(void);

		static double getTime(bool raw = false); // Time ellapsed in seconds
		static void freeze(void);
		static void unfreeze(void);
		static bool isFreezed(void);
		static void switchFreeze(void);
	private:
		static double time0, deltaFreeze, lastFreezeStart;
		static bool freezed;
		#if defined(_WIN32) || defined(_WIN64)
			static double freq;
		#endif
};

#endif // WORLD_HPP_INCLUDED
