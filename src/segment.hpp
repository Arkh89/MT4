#ifndef SEGMENT_HPP_INCLUDED
#define SEGMENT_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include "vect2D.hpp"


using namespace std;

typedef float TValue;
class Segment
{
	private:
		void updateNormalVector(void);
		Vect2D pt1,pt2,n;
	public:
		Segment(void);
		Segment(TValue _x1, TValue _y1, TValue _x2, TValue _y2);
		Segment(const Vect2D& vect1, const Vect2D& vect2);

		TValue getX1(void) const;
		TValue getX2(void) const;
		TValue getY1(void) const;
		TValue getY2(void) const;
		const Vect2D& getPt1(void) const;
		const Vect2D& getPt2(void) const;
		const Vect2D& getNormalVector(void) const;

		TValue length(void) const;
		TValue distSeg(const Vect2D& v) const; // Distance d'un point au segment
		void setPt1(const Vect2D& pt);
		void setPt2(const Vect2D& pt);
		void setLink1(const Segment& seg);
		void setLink2(const Segment& seg);
		Segment getInterval(const Segment& seg);
		Vect2D getPtSeg(TValue alp) const;
		Vect2D getCenter(void) const;

		void operator<<(const Segment& seg);
		void operator>>(const Segment& seg);
		Segment& operator*=(TValue s);
		Segment& operator/=(TValue s);

		bool intersection( const Segment& s1,float& x, float& y);
		Vect2D mirror(const Vect2D& spe);
};

#endif // SEGMENT_HPP_INCLUDED
