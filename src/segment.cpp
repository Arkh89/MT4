// A part ça vu que etherpad est en rade... j'ai fais les fonctions dont je me rappelais et je crois pas qu'il y en avait d'autres pour
// la classe segment, non ?
// Dernièrement: les foncions setlinks, milieu, point du segment avec alpha, getPt1, intervals
// Je pense que c'est a peu pres tout pour cette classe.On ajoutera plus tard si on a besoin...

#include <iostream>
#include "segment.hpp"

Segment::Segment(void)
{
}

Segment::Segment(TValue _x1, TValue _y1, TValue _x2, TValue _y2)
 : pt1(_x1,_y1), pt2(_x2,_y2)
{
	updateNormalVector();
}

Segment::Segment(const Vect2D& vect1, const Vect2D& vect2):pt1(vect1),pt2(vect2)
{
	updateNormalVector();

}

TValue Segment::getX1(void) const { return pt1.x; }
TValue Segment::getX2(void) const { return pt2.x; }
TValue Segment::getY1(void) const { return pt1.y; }
TValue Segment::getY2(void) const { return pt2.y; }

const Vect2D& Segment::getPt1(void) const {return pt1;}
const Vect2D& Segment::getPt2(void) const {return pt2;}

TValue Segment::length(void) const
{
	return sqrt( (pt2.x - pt1.x)*(pt2.x - pt1.x) + (pt2.y - pt1.y)*(pt2.y - pt1.y) );
}

TValue Segment::distSeg(const Vect2D& v) const
{
	if((pt2-pt1).scalarProd(v-pt1) * (pt2-pt1).scalarProd(v-pt2) > 0)
		return min((v-pt1).norm(),(v-pt2).norm());
	else
	{
		Vect2D proj = v - pt1;
		return proj.scalarProd(n);
	}
}

Vect2D Segment::getPtSeg(TValue alp)
{
	Vect2D v;
	v.x = (1-alp)*pt1.x + alp*pt2.x;
	v.y = (1-alp)*pt1.y + alp*pt2.y;
	return v;
	// return Vect2D((1-alp)*pt1 + (alp)*pt2); Bordel pourquoi cette ligne marche pas toute seule ?
	// J'ai même essayé Vect2D v1 = pt1; Vect2D = v2; return Vect2D((1-alp)*v1 + alp*pt2); Et même d'autres encore plus
	// décortiqués jusqu'à la version là au dessus qui me renvoit (enfin) plus l'erreur:
	// erreur: no match for ‘operator*’ in ‘(1.0e+0 - alp) * ((Segment*)this)->Segment::pt1’| ou variantes
	// Donc ué je comprends pas operator* est défini pour un Vect2D or pour moi ((Segment*)this)->Segment::pt1 == Vect2D non ?
	// Si t'as le temps dis moi pourquoi !! Thanks !
	// Elementaire mon cher Watson : tu as defini l'operateur* pour la classe Vect2D avec un TValue en argument. Du coup, pour appeler cette fonction il faut faire v*a, ou v est un Vect2D et a un TValue. Si tu fais a*v tu appelles la fonction operator* pour TValue avec en argument un Vect2D, ce qui n'est pas la meme fonction et qui n'est pas definie dans ton code (en plus). Pour y remedier, tu peux ecrire une fonction dans Vect2D.hpp/Vect2D.cpp mais a l'exterieur de la classe Vect2D : Vect2D operator*(TValue a, const Vect2D& v); qui va bien, OU choisir de toujours mettre dans l'ordre opppose : return Vect2D(pt1*(1-alp) + pt2*alp);
}

Vect2D Segment::getMilieu()
{
	Vect2D v = getPtSeg(0.5);
	return v; // Et meme plus : return getPtSeg(0.5);
}

void Segment::updateNormalVector(void)
{
	TValue d = length();
	n.x = - (pt2.y - pt1.y)/d;
	n.y =   (pt2.x - pt1.x)/d;
}

Segment Segment::getInterval(const Segment& seg)
{
	return Segment(pt2,seg.pt1); // Ok je vois Dupont effectivement c'est plus... concis ^^
}

void Segment::setPt1(const Vect2D& pt)
{
	pt1 = pt;
	updateNormalVector();
}

void Segment::setPt2(const Vect2D& pt)
{
	pt2 = pt;
	updateNormalVector();
}

void Segment::setLink1(const Segment& seg)
{
	pt1 = seg.pt2;
	updateNormalVector();
}

void Segment::setLink2(const Segment& seg)
{
	pt2 = seg.pt1;
	updateNormalVector();
}

// Il me semble que tu m'avais parlé d'un truc comme ça non pour les links, le faire avec les op << et >> ? enfin j'ai fait les deux... 
// Ok, je sais pas encore trop si l'on va s'en servir...
void Segment::operator<<(const Segment& seg)
{
	pt2 = seg.pt1;
	updateNormalVector();
}

void Segment::operator>>(const Segment& seg)
{
	pt1 = seg.pt2;
	updateNormalVector();
}


Segment& Segment::operator*=(TValue s)
{
 	pt2.x += (pt2.x - pt1.x)*s;
 	pt2.y += (pt2.y - pt1.y)*s;
 	return *this;
}

Segment& Segment::operator/=(TValue s)
{
 	pt2.x += (pt2.x - pt1.x)/s;
 	pt2.y += (pt2.y - pt1.y)/s;
 	return *this;
}


