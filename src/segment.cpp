
// J ai commencé mais marche pas pour l'instant les  constructeurs.... enfin...!

#include <iostream>
#include "segment.hpp"

Segment::Segment(void)
{
	v1 = new Vect2D(void);
	v2 = new Vect2D(void);
}

Segment::Segment(int _x1,int _x2,int _y1,int _y2)
{
	v1 = new Vect2D(int _x1,int _x2);
	v2 = new Vect2D(int _y1,int _y2);
}

Segment::Segment(const Vect2D& vect1, const Vect2D& vect2)
{
	v1 = new Vect2D(*vect1);
	v2 = new Vect2D(*vect2);
}
