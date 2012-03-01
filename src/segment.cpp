// J ai commencé mais marche pas pour l'instant les  constructeurs.... enfin...!

#include <iostream>
#include "segment.hpp"

Segment::Segment(void)
{
	v1 = new Vect2D(void); 
	v2 = new Vect2D(void);
	// We probably don't need to use pointers to Vect2D in this object since we know that a segment MUST have two vectors as members (this is not optional ;) ).
	// Thus, the members must be Vect2D objects (no reference/pointer) and we have to use initialization lists to init our objects (if necessary, so not in this constructor but in the two others)
}

Segment::Segment(int _x1,int _x2,int _y1,int _y2)
{
	v1 = new Vect2D(int _x1,int _x2);
	v2 = new Vect2D(int _y1,int _y2);
}

Segment::Segment(const Vect2D& vect1, const Vect2D& vect2)
{
	v1 = new Vect2D(*vect1); // warning : you declared your arguments as 'reference to a Vect2D', thus you don't need to use * to dereference/access the object (as in C for the pointers). That's why we love C++!
	v2 = new Vect2D(*vect2);
}
