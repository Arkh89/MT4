#ifndef SEGMENT_HPP_INCLUDED
#define SEGMENT_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include "vect2D.hpp"


using namespace std;


class Segment
{
	public:
		Segment(void);
		Segment(int _x1,int _x2,int _y1,int _y2);
		Segment(const Vect2D& vect1, const Vect2D& vect2);

		TValue distance(const Segment& seg) const; // taille du segment
		TValue distSeg(const Vect2D& v) const; // Distance d'un point au segment

		Segment& operator*=(TValue s);
		Segment& operator/=(TValue s);


	protected:

	private:
		Vect2D v1,v2,n;
};

#endif // SEGMENT_HPP_INCLUDED
