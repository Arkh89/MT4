#include <iostream>
#include <cmath>
#include "vect2D.hpp"


Vect2D::Vect2D(void) : Vector<TValue,2>::Vector()
{

}

Vect2D::Vect2D(TValue _x, TValue _y) : /*Vector<TValue,2>::Vector()*/ Vector<TValue,2>::Vector(_x,_y)
{

}

Vect2D::Vect2D(const Vect2D &v) : Vector<TValue,2>::Vector(v)
{

}

Vect2D::Vect2D(const Vector<TValue,2>& v) : Vector<TValue,2>::Vector(v)
{

}

Vect2D::Vect2D(TValue theta) : Vector<TValue,2>::Vector()
{
    coord[0] = (cos(theta));
    coord[1] = (sin(theta));
}

TValue& Vect2D::x(void)
{
    return coord[0];
}

TValue& Vect2D::y(void)
{
    return coord[1];
}

TValue Vect2D::getX(void) const
{
    return coord[0];
}

TValue Vect2D::getY(void) const
{
    return coord[1];
}

TValue Vect2D::angleX(void) const
{
	TValue theta = acos( coord[0]/norm() );
	return theta;
}
