#include <iostream>
#include <cmath>
#include "vect2D.hpp"

Vect2D::Vect2D(void)
 : x(0),y(0)
{ }

Vect2D::Vect2D(TValue _x, TValue _y)
 : x(_x),y(_y)
{ }

Vect2D::Vect2D(const Vect2D& v)
 : x(v.x),y(v.y)
{ }

Vect2D::Vect2D(TValue theta)
 : x(cos(theta)),y(sin(theta))
{ }

Vect2D Vect2D::operator+(const Vect2D& v) const
{
	Vect2D copie = v;
	copie += *this;
	return copie;
}

Vect2D Vect2D::operator-(const Vect2D& v) const
{
	Vect2D copie = v;
	copie -= *this;
	return copie;
}

Vect2D Vect2D::operator-() const
{
	Vect2D copie;
	copie.x = -x;
	copie.y = -y;
	return copie;
}

Vect2D Vect2D::operator*(const Vect2D& v) const
{
	Vect2D copie = v;
	copie.x = copie.x * (x);
	copie.y = copie.y * (y);
	return copie;
}

Vect2D Vect2D::operator/(const Vect2D& v) const
{
	Vect2D copie = v;
	copie.x = copie.x / (x);
	copie.y = copie.y / (y);
	return copie;
}

Vect2D Vect2D::operator*(TValue s) const
{
	Vect2D copie;
	copie.x = s * x;
	copie.y = s * y;
	return copie;
}

Vect2D Vect2D::operator/(TValue s) const
{
	Vect2D copie;
	copie.x = x / (s);
	copie.y = y / (s);
	return copie;
}


bool Vect2D::operator==(const Vect2D& v) const
{
	if(x == v.x && y == v.y)
		return true;
	else
		return false;
}

bool Vect2D::operator!=(const Vect2D& v) const
{
	if(x == v.x && y == v.y)
		return false;
	else
		return true;
}


Vect2D& Vect2D::operator+=(const Vect2D& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vect2D& Vect2D::operator-=(const Vect2D& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vect2D& Vect2D::operator*=(const Vect2D& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vect2D& Vect2D::operator/=(const Vect2D& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

Vect2D& Vect2D::operator*=(TValue s)
{
	x *= s;
	y *= s;
	return *this;
}

Vect2D& Vect2D::operator/=(TValue s)
{
	x /= s;
	y /= s;
	return *this;
}

TValue Vect2D::norm(void) const
{
	TValue dis = x*x + y*y;
	return  sqrt(dis);
}

void Vect2D::makeUnitary(void)
{
	TValue nor = norm();
	x /= nor;
	y /= nor;
}

Vect2D Vect2D::getUnitary(void) const
{
	Vect2D copie;
	TValue nor = norm();
	copie.x = x/nor;
	copie.y = y/nor;
	return copie;
}

TValue Vect2D::scalarProd(const Vect2D& v) const
{
	TValue sprod = x*v.x + y*v.y ;
	return sprod;
}

TValue Vect2D::distance(const Vect2D& v) const
{
	TValue d = sqrt((x-v.x)*(x-v.x)+(y-v.y)*(y-v.y));
	return d;
}

TValue Vect2D::angleX(void) const
{
	TValue theta = acos( x/norm() );
	return theta;
}

TValue Vect2D::angle(const Vect2D& v) const
{
	TValue theta = acos( scalarProd(v)/(norm()*v.norm()) );
	return theta;
}

ostream &operator<<( ostream &flux, Vect2D const& v)
{
	flux << '(' << v.x << ", " << v.y << ')';
	return flux;
}

///Useless comments
