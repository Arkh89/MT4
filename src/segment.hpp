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

		TValue distance(const Segment& seg) const; // taille du segment : a changer en length, non?
		TValue distSeg(const Vect2D& v) const; // Distance d'un point au segment

		Segment& operator*=(TValue s);
		Segment& operator/=(TValue s);


	protected:

	private:
		Vect2D v1,v2,n; // on utilisera plutot les noms pt1 et pt2 parce que ce ne sont plus des vecteurs mais vraiment des points (et ca aide a comprendre le code...)
};

#endif // SEGMENT_HPP_INCLUDED
