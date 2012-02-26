#include <iostream>
#include "math.h"
#include "vect2D.hpp"

Vect2D::Vect2D(void)
:x(0),y(0)
{ }

Vect2D::Vect2D(int _x, int _y)
:x(_x),y(_y)
{ }

Vect2D::Vect2D(const Vect2D& v)
:x(v.x),y(v.y)
{ }

Vect2D::Vect2D(TValue theta)
:x(cos(theta)),y(sin(theta))
{ }


Vect2D Vect2D::operator+(Vect2D &v) const
{
	Vect2D copie = v;
	copie += *this;
	return copie;
}

Vect2D Vect2D::operator-(Vect2D &v) const
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

Vect2D Vect2D::operator*(Vect2D &v) const
{
	Vect2D copie = v;
	copie.x = copie.x * (x);
	copie.y = copie.y * (y);
	return copie;
}

Vect2D Vect2D::operator/(Vect2D &v) const
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
	copie.y = y / (y);
	return copie;
}


bool Vect2D::operator==(Vect2D &v) const
{
	if(x == v.x && y == v.y)
		return true;
	else
		return false;
}

bool Vect2D::operator!=(Vect2D &v) const
{
	if(x == v.x && y == v.y)
		return false;
	else
		return true;
}


Vect2D& Vect2D::operator+=(const Vect2D &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vect2D& Vect2D::operator-=(const Vect2D &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vect2D& Vect2D::operator*=(const Vect2D &v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vect2D& Vect2D::operator/=(const Vect2D &v)
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






TValue Vect2D::norm() const
{
	TValue dis = pow(x,2) + pow(y,2);
	return  pow(dis,0.5);
}

void Vect2D::makeUnitary()
{
	TValue nor = norm();
	x /= nor;
	y /= nor;
}

Vect2D Vect2D::getUnitary() const
{
	Vect2D copie;
	TValue nor = norm();
	copie.x = x/nor;
	copie.y = y/nor;
	return copie;
}

TValue Vect2D::scalarProd(Vect2D &v) const
{
	TValue sprod = x*v.x + y*v.y ;
	return sprod;
}

TValue Vect2D::distance(Vect2D &v) const
{
	TValue d = pow(pow(x-v.x,2)+pow(y-v.y,2),0.5);
	return d;
}

TValue Vect2D::angleX() const
{
	Vect2D X(1,0);
	TValue theta = acos( scalarProd(X)/norm() );
	return theta;
}

TValue Vect2D::angle(Vect2D &v) const
{
	TValue theta = acos( scalarProd(v)/(norm()*v.norm()) );
	return theta;
}



ostream &operator<<( ostream &flux, Vect2D const& v)
{
	v.afficher(flux);
	return flux;
}

void Vect2D::afficher(ostream &flux) const
{
	flux << " x= " << x <<" y= " << y;
}





