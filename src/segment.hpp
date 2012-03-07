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
		Segment(TValue _x1, TValue _y1, TValue _x2, TValue _y2);
		Segment(const Vect2D& vect1, const Vect2D& vect2);

		TValue getX1(void) const;
		TValue getX2(void) const;
		TValue getY1(void) const;
		TValue getY2(void) const;

		TValue length(void) const;
		TValue distSeg(const Vect2D& v) const; // Distance d'un point au segment
		void setPt1(const Vect2D& pt);
		void setPt2(const Vect2D& pt);
		void setLink1(const Segment& seg);
		void setLink2(const Segment& seg);
		Segment getInterval(const Segment& seg);

		Segment& operator*=(TValue s);
		Segment& operator/=(TValue s);


	protected:

	private:
		void updateNormalVector(void);
		Vect2D pt1,pt2,n; // on utilisera plutot les noms pt1 et pt2 parce que ce ne sont plus des vecteurs mais vraiment des points (et ca aide a comprendre le code...)
};

#endif // SEGMENT_HPP_INCLUDED
