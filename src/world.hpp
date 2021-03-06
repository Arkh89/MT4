#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED
#include<ctime>
#include <iostream>
#include <vector>
#include "segment.hpp"
#include "body.hpp"

using namespace std;


class World
{
	private:
		static double time0;
		#if defined(_WIN32) || defined(_WIN64)
			static double freq;
		#endif

		double deltaFreeze, lastFreezeStart;
		bool freezed;
	public:

		World(void);
		~World(void);

		void freeze(void);
		void unfreeze(void);
		bool isFreezed(void);
		void switchFreeze(void);

		double getTime(bool raw = false); // Time ellapsed in seconds

		void addSeg(Segment& seg);
		void addBod(Body& bod);
		void delSeg(unsigned int i);
		void delBod(unsigned int i);

		std::vector<Segment> segments;
		std::vector<Body> bodies;
};

#endif // WORLD_HPP_INCLUDED
