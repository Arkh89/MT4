#ifndef VECT2D_HPP_INCLUDED
#define VECT2D_HPP_INCLUDED

#include "vector.hpp"

using namespace std;

typedef float TValue;

class Vect2D : public Vector<TValue,2>
{
public :
	Vect2D(void);
	Vect2D(TValue _x, TValue _y);
	Vect2D(const Vect2D& v);
	Vect2D(TValue theta);
	Vect2D(const Vector<TValue,2>& v);

	using Vector<TValue,2>::operator+=;
	using Vector<TValue,2>::operator-=;
	using Vector<TValue,2>::operator*=;
	using Vector<TValue,2>::operator/=;
	using Vector<TValue,2>::operator+;
	using Vector<TValue,2>::operator-;
	using Vector<TValue,2>::operator*;
	using Vector<TValue,2>::operator/;
	using Vector<TValue,2>::operator==;
	using Vector<TValue,2>::operator!=;

	TValue& x(void);
	TValue& y(void);
	TValue getX(void) const;
	TValue getY(void) const;
	TValue angleX(void) const;
};

#endif // VECT2D_HPP_INCLUDED
