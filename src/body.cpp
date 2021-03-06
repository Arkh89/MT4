#include "body.hpp"
#include <cmath>

Vect2D Body::gN = Vect2D(0.0,9.81);


Body::Body(void)
{ }

Body::Body(const Body& bod)
{
    pos = bod.pos;
    v = bod.v;
    R = bod.R;
    m = bod.m;
    k = bod.k;
    tI = bod.tI;
}

Body::Body(const Vect2D& pos0, double _m, double _k)
 : pos(pos0), m(_m), k(_k), tI(0.0)
{ }

Body::Body(const Vect2D& pos0, const Vect2D& v0, double _m, double _k)
 : pos(pos0), v(v0), m(_m), k(_k), tI(0.0)
{ }

Body::Body(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, const Vect2D& _R)
 : pos(pos0), v(v0), m(_m), k(_k), R(_R), tI(0.0)
{ }

Body::Body(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, const Vect2D& _R, double _tI)
 : pos(pos0), v(v0), m(_m), k(_k), R(_R), tI(_tI)
{ }

Body::~Body(void)
{ }


Vect2D Body::trajectory(double t)
{
    Vect2D Dv;
    Dv.x() = (m/k) * ((m/k)*gN.getX() + v.getX() + (R.getX()/k) ) * (1.0 - exp(-(k/m)*  (t - tI) ))  -  (m/k) * gN.getX() * (t - tI)  + (R.getX()/k) * (t - tI);
    Dv.y() = (m/k) * ((m/k)*gN.getY() + v.getY() + (R.getY()/k) ) * (1.0 - exp(-(k/m)*  (t - tI) ))  -  (m/k) * gN.getY() * (t - tI)  + (R.getY()/k) * (t - tI);
    return Dv;
}

Vect2D Body::getCurSp(double t)
{
    Vect2D DvS;
    DvS.x() = ((m/k)*gN.getX() + v.getX() + (R.getX()/k) ) * (exp(-(k/m)*  (t - tI) ))  -  (m/k) * gN.getX() + (R.getX()/k);
    DvS.y() = ((m/k)*gN.getY() + v.getY() + (R.getY()/k) ) * (exp(-(k/m)*  (t - tI) ))  -  (m/k) * gN.getY() + (R.getY()/k);
    return DvS;
}

Vect2D Body::getCurPos(double t)
{
    return pos + trajectory(t);
}

Vect2D Body::getSp(void)
{
    return v;
}

Vect2D Body::getPos(void)
{
    return pos;
}

void Body::setNewSpeed(Vect2D s,double ti)
{
    pos += trajectory(ti);
    tI = ti;
    v = s;
}

void Body::teleport(const Vect2D& p, double ti)
{
    pos = p;
    tI = ti;
}

void Body::setGrav(Vect2D gNew)
{
    gN = gNew;
}


Body& Body::operator=(const Body& bod)
{
	pos = bod.pos;
	v = bod.v;
	R = bod.R;
	m = bod.m;
	k = bod.k;
	tI = bod.tI;
	return *this;
}
