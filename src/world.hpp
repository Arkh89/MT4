#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

using namespace std;


class World
{
	public:

		World(void);
		~World(void);
		static double getTime(void); // Time ellapsed in ms
		static double setTime(double t);
	private:
		static double time0;
};

#endif // WORLD_HPP_INCLUDED
