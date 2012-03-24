#ifndef BOUNDINGBOX_HPP_INCLUDED
#define BOUNDINGBOX_HPP_INCLUDED

#include "body.hpp"

class BoundingBox : public Body
{
	public:
		BoundingBox(void);
		BoundingBox(const Vect2D& pos0, double _m, double _k, double _W, double _H);
		BoundingBox(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, double _W, double _H);
		BoundingBox(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, const Vect2D& _R, double _W, double _H);
		BoundingBox(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, const Vect2D& _R, double _tI, double _W, double _H);
		~BoundingBox(void);

	private:
		double W,H; // Width & Height
};

#endif // BOUNDINGBOX_HPP_INCLUDED
