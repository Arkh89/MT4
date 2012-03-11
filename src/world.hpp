#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

using namespace std;


class World
{
	public:
		World(void);
		static int getTime(); // Time ellapsed in ms
	private:
		clock_t time0;
		static int time;
};



#endif // WORLD_HPP_INCLUDED
