#include <iostream>
#include <cmath>
#include "color.hpp"

typedef unsigned char TValue;

Color::Color(void) : Vector<TValue,4>::Vector()
{

}

Color::Color(TValue _R, TValue _G, TValue _B, TValue _A)
{
	R() = _R;
	G() = _G;
	B() = _B;
	A() = _A;
}

Color::Color(const Color &v) : Vector<TValue,4>::Vector(v)
{

}

Color::Color(const Vector<TValue,4>& v) : Vector<TValue,4>::Vector(v)
{

}

TValue& Color::R(void)
{
	return coord[0];
}

TValue& Color::G(void)
{
	return coord[1];
}

TValue& Color::B(void)
{
	return coord[2];
}

TValue& Color::A(void)
{
	//TValue a = 255*coord[3];
	return coord[3];
}

TValue Color::getR(void) const
{
	return coord[0];
}

TValue Color::getG(void) const
{
	return coord[1];
}

TValue Color::getB(void) const
{
	return coord[2];
}

TValue Color::getA(void) const
{
	//TValue a=255*coord[3];
	return coord[3];
}

TValue Color::hue(void) const
{
	double pi=3.14159265358979323846;

	return 180/pi*atan2(sqrt(3)*(coord[1]-coord[2]) , 2*coord[0]-coord[1]-coord[2]);
}

TValue Color::brightness(void) const
{
	TValue M=max(coord[0],max(coord[1],coord[2]));
	TValue m=min(coord[0],min(coord[1],coord[2]));

	return 0.5*M+0.5*m;
}

TValue Color::saturation(void) const
{
	TValue M=max(coord[0],max(coord[1],coord[2]));
	TValue m=min(coord[0],min(coord[1],coord[2]));

	TValue C=M-m;
	TValue S=0;
	TValue B=Color::brightness();

	if(C!=0)
	{
		S=C/(1-abs(static_cast<float>(2*B-1)));
	}

	return S;
}


