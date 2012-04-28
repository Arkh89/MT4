#include <iostream>
#include "segment.hpp"

Segment::Segment(void)
{

}

Segment::Segment(const Segment& seg)
{
	pt1 = seg.pt1;
	pt2 = seg.pt2;
	n = seg.n;
}

Segment::Segment(TValue _x1, TValue _y1, TValue _x2, TValue _y2)
 : pt1(_x1,_y1), pt2(_x2,_y2)
{
    updateNormalVector();
}

Segment::Segment(const Vect2D& vect1, const Vect2D& vect2)
 : pt1(vect1), pt2(vect2)
{
    updateNormalVector();

}

Segment::~Segment(void)
{
}

TValue Segment::getX1(void) const { return pt1.getX(); }
TValue Segment::getX2(void) const { return pt2.getX(); }
TValue Segment::getY1(void) const { return pt1.getY(); }
TValue Segment::getY2(void) const { return pt2.getY(); }

const Vect2D& Segment::getPt1(void) const {return pt1;}
const Vect2D& Segment::getPt2(void) const {return pt2;}
const Vect2D& Segment::getNormalVector(void) const {return n;}

TValue Segment::length(void) const
{
    return sqrt( (pt2.getX() - pt1.getX())*(pt2.getX() - pt1.getX()) + (pt2.getY() - pt1.getY())*(pt2.getY() - pt1.getY()) );
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


Vect2D Segment::getPtSeg(TValue alp) const
{
    return Vect2D((1-alp)*pt1 + alp*pt2);
}

Vect2D Segment::getCenter(void) const
{
    return getPtSeg(0.5);
}

void Segment::updateNormalVector(void)
{
    TValue d = length();
    n.x() = - (pt2.y() - pt1.y())/d;
    n.y() =   (pt2.x() - pt1.x())/d;
}

Segment Segment::getInterval(const Segment& seg)
{
    return Segment(pt2,seg.pt1);
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

Segment& Segment::operator=(const Segment& seg)
{
    pt1 = seg.pt1;
    pt2 = seg.pt2;
    n=seg.n;
    return *this;
}


Segment& Segment::operator*=(TValue s)
{
    pt2.x() += (pt2.x() - pt1.x())*s;
    pt2.y() += (pt2.y() - pt1.y())*s;
    return *this;
}

Segment& Segment::operator/=(TValue s)
{
    pt2.x() += (pt2.x() - pt1.x())/s;
    pt2.y() += (pt2.y() - pt1.y())/s;
    return *this;
}




bool Segment::intersection( const Segment& s,float& a, float& b)
{
    float denom = (pt2.getX()-pt1.getX())*(s.pt2.getY()-s.pt1.getY())-(pt2.getY()-pt1.getY())*(s.pt2.getX()-s.pt1.getX());
    // (Bx-Ax)(Dy-Cy)-(By-Ay)(Dx-Cx)

    if(denom<1e-6)
        return false;

    a = ((pt1.getY()-s.pt1.getY())*(s.pt2.getX()-s.pt1.getX())-(pt1.getX()-s.pt1.getX())*(s.pt2.getY()-s.pt1.getY())) / denom;
    // (Ay-Cy)(Dx-Cx)-(Ax-Cx)(Dy-Cy)
    b = ((pt1.getY()-s.pt1.getY())*(pt2.getX()-pt1.getX())-(pt1.getX()-s.pt1.getX())*(pt2.getY()-pt1.getY())) / denom;
    // (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)

    if(0.0<=a && a<=1.0 && 0.0<=b && b<=1.0)
        return true;
    else
    {
        a = 0.0f;
        b = 0.0f;
        return false;
    }
}

Vect2D Segment::mirror(const Vect2D& spe)
{
	return spe + (- 2.0f*(n.scalarProd(spe))*n);
}
