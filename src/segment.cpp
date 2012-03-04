// Le calcul de la normale est fait dans les constructeurs (je suis pas sûr que ce soit le bon endroit ?)
// Et deuxième point c'est un vecteur unitaire d'origine en zéro du coup

#include <iostream>
#include "segment.hpp"



Segment::Segment(void):v1(),v2(),n()
{
}

Segment::Segment(int _x1,int _x2,int _y1,int _y2):v1(_x1,_y1),v2(_x2,_y2)
{
	TValue D = (_y2 - _y1) / (_x2 - _x1);
	n.x = - ( D ) / sqrt(1 + D*D);
	n.y = + ( 1 ) / sqrt(1 + D*D);
}

Segment::Segment(const Vect2D& vect1, const Vect2D& vect2):v1(vect1),v2(vect2)
{
	TValue D = (v2.y - v1.y) / (v2.x - v1.x);
	n.x = - ( D ) / sqrt(1 + D*D);
	n.y = + ( 1 ) / sqrt(1 + D*D);
}



TValue Segment::distance(const Segment& seg) const
{
	TValue dist = sqrt( (v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y) );
	return dist;
}


TValue Segment::distSeg(const Vect2D& v) const
{
	Vect2D segV( v2.x - v1.x, v2.y - v1.y );
	TValue D = segV.y / segV.y;
	TValue DSeg = segV.Vect2D::scalarProd(v) / sqrt(1 + D*D);
	return DSeg;
}



// Pour les operateurs += et -= comme ça je vois pas trop l'intérêt ni la signification avec segment parce que l'angle
// n'est pas conservé... (idée?)
// Et pour *= et /= uniquement par un scalaire ( je vois pas la sgnification de multiplier deux segments ou encore de les diviser entre eux).
// Mais pour la multiplication ou la division par un scalaire j'ai deux versions qui me viennent, une a priori bête on multiplie
// les deux vecteurs par s du coup le segment conserve l'angle et s-uple sa norme mais n' plus la même origine. Ou la version deux
// que j'imagine plus on conserve angle et origine mais on s-uple la norme

// Version 1

Segment& Segment::operator*=(TValue s)
{
	v1 *= s;
	v2 *= s;
	return *this;
}

Segment& Segment::operator/=(TValue s)
{
	v1 /= s;
	v2 /= s;
	return *this;
}

// Version 2
// Segment& Segment::operator*=(TValue s)
// {
// 	v2.x += (v2.x - v1.x)*s;
// 	v2.y += (v2.y - v1.y)*s;
// 	return *this;
// }

// Segment& Segment::operator/=(TValue s)
// {
// 	v2.x += (v2.x - v1.x)/s;
// 	v2.y += (v2.y - v1.y)/s;
// 	return *this;
// }



