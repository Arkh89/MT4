#ifndef SEGMENT_HPP_INCLUDED
#define SEGMENT_HPP_INCLUDED

#include <iostream>
#include "vect2D.hpp"


using namespace std;

typedef float TValue; // Not needed here because we already included header file vect2D.hpp which contains this definition.

class Segment
{
	public:
		Segment(void);
		Segment(int _x1,int _x2,int _y1,int _y2);
		Segment(const Vect2D& vect1, const Vect2D& vect2);

		virtual ~Segment(void);
		// I have never used a virtual destructor in my whole life. Please don't do that too, unless you know *exactly* what you are doing. And, I agree that in the current design with dynamically set objects we have to clean them in the desctuctor but we won't need it if we use directly the object (see next comment about that) because the call is implicit.
		
	protected:

	private:
	Vect2D* v1,v2,n; //We don't need dynamic object here, just use Vect2D v1,v2,n and the initialization list constructor(arguments) : initializationList
};

#endif // SEGMENT_HPP_INCLUDED
