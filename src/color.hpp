#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

#include "vector.hpp"

using namespace std;

//typedef unsigned char TValue;

class Color : public Vector<unsigned char,4>
{
	public:
	Color(void);
	Color(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A);
	Color(const Color& v);
	Color(const Vector<unsigned char,4>& v);

	using Vector<unsigned char,4>::operator+=;
	using Vector<unsigned char,4>::operator-=;
	using Vector<unsigned char,4>::operator*=;
	using Vector<unsigned char,4>::operator/=;
	using Vector<unsigned char,4>::operator+;
	using Vector<unsigned char,4>::operator-;
	using Vector<unsigned char,4>::operator*;
	using Vector<unsigned char,4>::operator/;
	using Vector<unsigned char,4>::operator==;
	using Vector<unsigned char,4>::operator!=;

	unsigned char& R(void);
	unsigned char& G(void);
	unsigned char& B(void);
	unsigned char& A(void);
	unsigned char getR(void) const;
	unsigned char getG(void) const;
	unsigned char getB(void) const;
	unsigned char getA(void) const;
	unsigned char hue(void) const;
	unsigned char brightness(void) const;
	unsigned char saturation(void) const;
	// Set of Color with HSL
	/*void setHue (double h);
 	void setHue (double h);
 	void setHue (double h);*/


};

#endif // COLOR_H
