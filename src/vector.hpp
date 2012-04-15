#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED
#include <iostream>
#include <cmath>
#include <cstdarg>

using namespace std;



template<typename TValue, unsigned int d>
    class Vector
    {
        public :
        TValue coord[d];
        static const unsigned int dim=d;
        typedef TValue Type;

        Vector(void); // x = 0, y = 0
        Vector(TValue _x,...);
        //Vector(TValue _x, TValue _y); // x = _x,y = _y ///To remove and replace by a proper constructor in D-dimension. NOT YET IMPLEMENTED
        Vector(const Vector& v); // x = v.x, y = v.y
        //Vector(TValue theta); //To place in Vect2D.hpp as a specific implementation for this subclass. NOT YET IMPLEMENTED

        Vector& operator+=(const Vector& v);
        Vector& operator-=(const Vector& v);
        Vector& operator*=(const Vector& v);
        Vector& operator/=(const Vector& v);
        Vector& operator*=(TValue s);
        Vector& operator/=(TValue s);

        Vector operator+(const Vector& v) const;
        Vector operator-(const Vector& v) const;
        Vector operator-(void) const;
        Vector operator*(const Vector& v) const;
        Vector operator/(const Vector& v) const;
        Vector operator*(TValue s) const;
        Vector operator/(TValue s) const;
        bool   operator==(const Vector& v) const;
        bool   operator!=(const Vector& v) const;

        TValue& operator[](unsigned int i);

        void makeUnitary(void);

        TValue norm(void) const;
        TValue distance(const Vector& v) const;
        TValue scalarProd(const Vector& v) const;
        TValue angle(const Vector& v) const;
        //TValue angleX(void) const; //Unusable here. Planned for the Vect2D subclass
        Vector getUnitary(void) const;
    };

template<typename T, unsigned int d>
    Vector<T,d> operator*(T s, const Vector<T,d>& v);
template<typename T, unsigned int d>
    Vector<T,d> operator/(T s, const Vector<T,d>& v);
template<typename T, unsigned int d>
    ostream &operator<<( ostream &flux, Vector<T,d> const& v);
/*
typedef float TValue;

    class Vect2D
    {
        public :
        TValue x,y;

        Vect2D(void); // x = 0, y = 0
        Vect2D(TValue _x, TValue _y); // x = _x,y = _y
        Vect2D(const Vect2D& v); // x = v.x, y = v.y
        Vect2D(TValue theta); //

        Vect2D& operator+=(const Vect2D& v);
        Vect2D& operator-=(const Vect2D& v);
        Vect2D& operator*=(const Vect2D& v);
        Vect2D& operator/=(const Vect2D& v);
        Vect2D& operator*=(TValue s);
        Vect2D& operator/=(TValue s);

        Vect2D operator+(const Vect2D& v) const;
        Vect2D operator-(const Vect2D& v) const;
        Vect2D operator-(void) const;
        Vect2D operator*(const Vect2D& v) const;
        Vect2D operator/(const Vect2D& v) const;
        Vect2D operator*(TValue s) const;
        Vect2D operator/(TValue s) const;
        bool   operator==(const Vect2D& v) const;
        bool   operator!=(const Vect2D& v) const;

        void makeUnitary(void);

        TValue norm(void) const;
        TValue distance(const Vect2D& v) const;
        TValue scalarProd(const Vect2D& v) const;
        TValue angle(const Vect2D& v) const;
        TValue angleX(void) const;
        Vect2D getUnitary(void) const;
    };

    Vect2D operator*(TValue s, const Vect2D& v);
    Vect2D operator/(TValue s, const Vect2D& v);
        ostream &operator<<( ostream &flux, Vect2D const& v);
*/

template<typename T, unsigned int d>
Vector<T,d>::Vector()
{
    for(int i(0); i<dim; i++)
        coord[i]=0;
}

template<typename T, unsigned int d>
Vector<T,d>::Vector(T _x,...)
{
    va_list coordl;
    va_start(coordl, _x);
    for(int i(1); i<dim; i++)
        coord[i] = va_arg(coordl,T);
    va_end(coordl);

}

///Implement here the new general constructor.
/*Vect2D::Vect2D(TValue _x, TValue _y)
 : x(_x),y(_y)
{ }*/

template<typename T, unsigned int d>
Vector<T,d>::Vector(const Vector<T,d>& v)
{
    for(int i(0); i<dim; i++)
            coord[i]=v.coord[i];
}

///To remove.
/*Vect2D::Vect2D(TValue theta)
 : x(cos(theta)),y(sin(theta))
{ }*/

template<typename T, unsigned int d>
Vector<T,d> Vector<T,d>::operator+(const Vector<T,d>& v) const
{
    Vector copie = v;
    copie += *this;
    return copie;
}

template<typename T, unsigned int d>
Vector<T,d> Vector<T,d>::operator-(const Vector<T,d>& v) const
{
    Vector copie = v;
    copie -= *this;
    return copie;
}

template<typename T, unsigned int d>
Vector<T,d> Vector<T,d>::operator-() const
{
    Vector copie;
    for(int i(0); i<dim; i++)
        copie.coord[i] = -coord[i];
    return copie;
}

template<typename T, unsigned int d>
Vector<T,d> Vector<T,d>::operator*(const Vector<T,d>& v) const
{
    Vector copie = v;
    for(int i(0); i<dim; i++)
        copie.coord[i] = copie.coord[i] * (coord[i]);
    return copie;
}

template<typename T, unsigned int d>
Vector<T,d> Vector<T,d>::operator/(const Vector<T,d>& v) const
{
    Vector copie = v;
    for(int i(0); i<dim; i++)
        copie.coord[i] = copie.coord[i] / (coord[i]);
    return copie;
}

template<typename T, unsigned int d>
Vector<T,d> Vector<T,d>::operator*(T s) const
{
    Vector copie;
    for(int i(0); i<dim; i++)
        copie.coord[i] = s * (coord[i]);
    return copie;
}

template<typename T, unsigned int d>
Vector<T,d> Vector<T,d>::operator/(T s) const
{
    Vector copie;
    for(int i(0); i<dim; i++)
        copie.coord[i] = (coord[i])/ (s);
    return copie;
}

template<typename T, unsigned int d>
bool Vector<T,d>::operator==(const Vector<T,d>& v) const
{
    for(int i(0); i<dim; i++)
    {
        if(coord[i] != v.coord[i])
            return false;
    }
    return true;
}

template<typename T, unsigned int d>
bool Vector<T,d>::operator!=(const Vector<T,d>& v) const
{
    for(int i(0); i<dim; i++)
    {
        if(coord[i] != v.coord[i])
            return true;
    }
    return false;
}

template<typename T, unsigned int d>
T& Vector<T,d>::operator[](unsigned int i)
{
    /*
    if(i<dim)
        return coord[i];
    else
        return WRITE AN ERROR HERE;
        Well, I suppose we have to check the length of the vector, but I'm unsure of the mean to handle the error...
        */
    return coord[i];
}


template<typename T, unsigned int d>
Vector<T,d>& Vector<T,d>::operator+=(const Vector<T,d>& v)
{
    for(int i(0); i<dim; i++)
        coord[i] += v.coord[i];
    return *this;
}

template<typename T, unsigned int d>
Vector<T,d>& Vector<T,d>::operator-=(const Vector<T,d>& v)
{
    for(int i(0); i<dim; i++)
        coord[i] -= v.coord[i];
    return *this;
}

template<typename T, unsigned int d>
Vector<T,d>& Vector<T,d>::operator*=(const Vector<T,d>& v)
{
    for(int i(0); i<dim; i++)
        coord[i] *= v.coord[i];
    return *this;
}

template<typename T, unsigned int d>
Vector<T,d>& Vector<T,d>::operator/=(const Vector<T,d>& v)
{
    for(int i(0); i<dim; i++)
        coord[i] /= v.coord[i];
    return *this;
}

template<typename T, unsigned int d>
Vector<T,d>& Vector<T,d>::operator*=(T s)
{
    for(int i(0); i<dim; i++)
        coord[i] *= s;
    return *this;
}

template<typename T, unsigned int d>
Vector<T,d>& Vector<T,d>::operator/=(T s)
{
    for(int i(0); i<dim; i++)
        coord[i] /= s;
    return *this;
}

template<typename T, unsigned int d>
T Vector<T,d>::norm(void) const
{
    T dis = 0;
    for(int i(0); i<dim; i++)
        dis += (coord[i]*coord[i]);
    return  sqrt(dis);
}

template<typename T, unsigned int d>
void Vector<T,d>::makeUnitary(void)
{
    T nor = norm();
    for(int i(0); i<dim; i++)
        coord[i] /= nor;
}

template<typename T, unsigned int d>
Vector<T,d> Vector<T,d>::getUnitary(void) const
{
    Vector copie;
    T nor = norm();
    for(int i(0); i<dim; i++)
        copie.coord[i] = coord[i]/nor;
    return copie;
}

template<typename T, unsigned int d>
T Vector<T,d>::scalarProd(const Vector<T,d>& v) const
{
    T sprod(0);
    for(int i(0); i<dim; i++)
        sprod += coord[i]*v.coord[i];
    return sprod;
}

template<typename T, unsigned int d>
T Vector<T,d>::distance(const Vector<T,d>& v) const
{
    T dist(0);
    for(int i(0); i<dim; i++)
        dist += (coord[i]-v.coord[i]) * (coord[i]-v.coord[i]);
    return sqrt(dist);
}

/*TValue Vector::angleX(void) const
{
    TValue theta = acos( x/norm() );
    return theta;
}*/ // a refaire pour les Vect2D uniquement.

template<typename T, unsigned int d>
T Vector<T,d>::angle(const Vector<T,d>& v) const //I think this one is just fine for D-dimension, if cosine is define for the TValue type.
{
    T theta = acos( scalarProd(v)/(norm()*v.norm()) );
    return theta;
}

template<typename T, unsigned int d>
ostream &operator<<( ostream &flux, Vector<T,d> const& v)
{
    flux << '(';
    for(int i(0); i<(v.dim-1); i++)
        flux << v.coord[i] << ", ";
    flux << v.coord(v.dim-1) << ')';
    return flux;
}

template<typename T, unsigned int d>
Vector<T,d> operator*(T s, const Vector<T,d>& v)
{
    Vector<T,d> vect;
    for(int i(0); i<v.dim; i++)
        vect.coord[i] = s * v.coord[i];
    return vect;
}

template<typename T, unsigned int d>
Vector<T,d> operator/(T s, const Vector<T,d>& v)
{
    Vector<T,d> vect;
    for(int i(0); i<v.dim; i++)
        vect.coord[i] = s / v.coord[i];
    return vect;
}


#endif // VECTOR_HPP_INCLUDED
