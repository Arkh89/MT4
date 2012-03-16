#include "body.hpp"
#include <cmath>

double Body::gN = 9.81;


Body::Body(void)
{ }

Body::Body(Vect2D pos0, double _m, double _k)
 : pos(pos0), m(_m), k(_k)
{ }

Body::Body(Vect2D pos0, Vect2D v0, double _m, double _k)
 : pos(pos0), v(v0), m(_m), k(_k)
{ }

Body::Body(Vect2D pos0, Vect2D v0, double _m, double _k, Vect2D _R)
 : pos(pos0), v(v0), m(_m), k(_k), R(_R)
{ }

Body::~Body(void)
{ }


Vect2D Body::trajectory(double t)
{
	Vect2D Dv;
	Dv.x = (m/k) * (v.x) * (1 - exp(-(k/m)*t)) + (R.x/k) * t;
	Dv.y = (m/k) * ((m/k)*gN + v.y) * (1 - exp(-(k/m)*t))  -  (m/k) * gN * t  + (R.y/k) * t;
	return Dv;
}

Vect2D Body::getCurPos(double t)
{
	return pos = trajectory(t);
}


void Body::setGrav(double gNew)
{
	gN = gNew;
}
