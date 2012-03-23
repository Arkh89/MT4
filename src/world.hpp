#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED
#include<ctime>

using namespace std;


class World
{
	public:

		World(void);
		~World(void);
		static double getTime(void); // Time ellapsed in seconds
	private:
		static double time0;
		#if defined(_WIN32) || defined(_WIN64)
			static double freq;
		#endif
};

#endif // WORLD_HPP_INCLUDED
