#include <iostream>
#include "segment.hpp"

Segment::Segment(void)
{
}

Segment::Segment(TValue _x1, TValue _y1, TValue _x2, TValue _y2)
 : pt1(_x1,_y1), pt2(_x2,_y2)
{
	updateNormalVector();
}

Segment::Segment(const Vect2D& vect1, const Vect2D& vect2):pt1(vect1),pt2(vect2)
{
	updateNormalVector();

}

TValue Segment::getX1(void) const { return pt1.x; }
TValue Segment::getX2(void) const { return pt2.x; }
TValue Segment::getY1(void) const { return pt1.y; }
TValue Segment::getY2(void) const { return pt2.y; }

TValue Segment::length(void) const
{
	return sqrt( (pt2.x - pt1.x)*(pt2.x - pt1.x) + (pt2.y - pt1.y)*(pt2.y - pt1.y) );
}


TValue Segment::distSeg(const Vect2D& v) const
{

	if((pt2-pt1).scalarProd(v-pt1) * (pt2-pt1).scalarProd(v-pt2) > 0)
		return min((v-pt1).norm(),(v-pt2).norm());
	else
	{
		Vect2D proj = v - pt1;
		return proj.scalarProd(n);
	}
}


void Segment::updateNormalVector(void)
{
	TValue d = length();
	n.x = - (pt2.y - pt1.y)/d;
	n.y =   (pt2.x - pt1.x)/d;
}



void Segment::setPt1(const Vect2D& pt)
{
	pt1 = pt;
}

void Segment::setPt2(const Vect2D& pt)
{
	pt2 = pt;
}

void Segment::setLink1(const Segment& seg)
{
	pt1 = seg.pt2;
}

void Segment::setLink2(const Segment& seg)
{
	pt2 = seg.pt1;
}

Segment Segment::getInterval(const Segment& seg)
{
	Segment inter;
	inter.pt1 = pt2;
	inter.pt2 = seg.pt1;
	return inter;
}


Segment& Segment::operator*=(TValue s)
{
 	pt2.x += (pt2.x - pt1.x)*s;
 	pt2.y += (pt2.y - pt1.y)*s;
 	return *this;
}

Segment& Segment::operator/=(TValue s)
{
 	pt2.x += (pt2.x - pt1.x)/s;
 	pt2.y += (pt2.y - pt1.y)/s;
 	return *this;
}
