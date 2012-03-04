// Le calcul de la normale est fait dans les constructeurs (je suis pas sûr que ce soit le bon endroit ?)
// Et deuxième point c'est un vecteur unitaire d'origine en zéro du coup

/// Oui, enfin un veteur ca ne part d'une origine. En plus, il faudrait faire une fonction privee updateNormalVector(void) qui le fasse et qui soit appellee depuis les constructeurs et aussi depuis deux accesseurs void setPt1(const Vect2D& pt); et void setPt2(const Vect2D& pt);.

/// On pourrait aussi faire deux fonctions setLink1(const Segment& seg) qui ferait en sorte de mettre le pt1 de this egal au pt2 de seg, et setLink2(const Segment& seg) qui ferait la meme chose pour pt2 de this et pt1 de seg

/// on pourrait aussi faire une fonction Segment getInterval(const Segment& seg) qui retournerait un segment entre les points this->pt2 et seg.pt1.

#include <iostream>
#include "segment.hpp"

Segment::Segment(void)
 : v1(), v2(), n() /// pas utile, si ce n'est pas explicitement specifie, ce constructeur va appeller automatiquement les constructeurs par defaut de ces objets...
{
}

Segment::Segment(TValue _x1, TValue _y1, TValue _x2, TValue _y2)
 : v1(_x1,_y1), v2(_x2,_y2)
{
	/// Me donne un beau "Floating Exception" (erreur de calcul = division par 0)
	/// Que se passe t'il lorsqu'on a un vecteur vertical? x2==x1?
	//TValue D = (_y2 - _y1) / (_x2 - _x1);
	//n.x = - ( D ) / sqrt(1 + D*D);
	//n.y = + ( 1 ) / sqrt(1 + D*D);

	/// Pour moi l'algo de la normale c'est plutot :
	TValue d = length();
	n.x = - (v2.y - v1.y)/d;
	n.y =   (v2.x - v1.x)/d;
}

Segment::Segment(const Vect2D& vect1, const Vect2D& vect2):v1(vect1),v2(vect2)
{
	TValue D = (v2.y - v1.y) / (v2.x - v1.x);
	n.x = - ( D ) / sqrt(1 + D*D);
	n.y = + ( 1 ) / sqrt(1 + D*D);
}

TValue Segment::getX1(void) const { return v1.x; }
TValue Segment::getX2(void) const { return v2.x; }
TValue Segment::getY1(void) const { return v1.y; }
TValue Segment::getY2(void) const { return v2.y; }

TValue Segment::length(void) const
{
	return sqrt( (v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y) );
}


TValue Segment::distSeg(const Vect2D& v) const
{
	TValue D = (v2.x - v1.x) / (v2.y - v1.y);
	TValue DSeg = n.Vect2D::scalarProd(v) / sqrt(1 + D*D);
	return DSeg;
	/// Euh je connais pas ces formules...
	/// Vect2D proj = v - v1;
	/// return proj.scalarProd(n);

	/// Et ca c'est pour la distance a une droite mais pas la distance a un segment.
	/// Tu peux utiliser un papier et un crayon pour t'en persuader... 8)
}



// Pour les operateurs += et -= comme ça je vois pas trop l'intérêt ni la signification avec segment parce que l'angle
// n'est pas conservé... (idée?)
// Et pour *= et /= uniquement par un scalaire ( je vois pas la sgnification de multiplier deux segments ou encore de les diviser entre eux).
// Mais pour la multiplication ou la division par un scalaire j'ai deux versions qui me viennent, une a priori bête on multiplie
// les deux vecteurs par s du coup le segment conserve l'angle et s-uple sa norme mais n' plus la même origine. Ou la version deux
// que j'imagine plus on conserve angle et origine mais on s-uple la norme

/// Je suis pas certain que ca soit utile d'avoir des arguments...

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
