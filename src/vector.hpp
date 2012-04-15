#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED
#include <iostream>
#include <cmath>

using namespace std;



template<typename TValue, unsigned int dim>
    class Vector
    {
        public :
        TValue coord[dim];
        static const unsigned int dimension=dim;
        typedef TValue Type;

        Vector(void); // x = 0, y = 0
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

        void makeUnitary(void);

        TValue norm(void) const;
        TValue distance(const Vector& v) const;
        TValue scalarProd(const Vector& v) const;
        TValue angle(const Vector& v) const;
        //TValue angleX(void) const; //Unusable here. Planned for the Vect2D subclass
        Vector getUnitary(void) const;
    };

template<typename T, unsigned int dim>
    Vector<T,dim> operator*(T s, const Vector<T,dim>& v);
template<typename T, unsigned int dim>
    Vector<T,dim> operator/(T s, const Vector<T,dim>& v);
template<typename T, unsigned int dim>
    ostream &operator<<( ostream &flux, Vector<T,dim> const& v);
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

template<typename T, unsigned int dim>
Vector<T,dim>::Vector(void)
{
    for(int i(0); i<dim; i++)
        coord[i]=0;
}


///Implement here the new general constructor.
/*Vect2D::Vect2D(TValue _x, TValue _y)
 : x(_x),y(_y)
{ }*/

template<typename T, unsigned int dim>
Vector<T,dim>::Vector(const Vector& v)
{
    if(dim == v.dimension)
    {
        for(int i(0); i<dim; i++)
            coord[i]=v.coord[i];
    }
}

///To remove.
/*Vect2D::Vect2D(TValue theta)
 : x(cos(theta)),y(sin(theta))
{ }*/

template<typename T, unsigned int dim>
Vector<T,dim> Vector<T,dim>::operator+(const Vector& v) const
{
    Vector copie = v;
    copie += *this;
    return copie;
}

template<typename T, unsigned int dim>
Vector<T,dim> Vector<T,dim>::operator-(const Vector& v) const
{
    Vector copie = v;
    copie -= *this;
    return copie;
}

template<typename T, unsigned int dim>
Vector<T,dim> Vector<T,dim>::operator-() const
{
    Vector copie;
    for(int i(0); i<dim; i++)
        copie.coord[i] = -coord[i];
    return copie;
}

template<typename T, unsigned int dim>
Vector<T,dim> Vector<T,dim>::operator*(const Vector& v) const
{
    Vector copie = v;
    for(int i(0); i<dim; i++)
        copie.coord[i] = copie.coord[i] * (coord[i]);
    return copie;
}

template<typename T, unsigned int dim>
Vector<T,dim> Vector<T,dim>::operator/(const Vector& v) const
{
    Vector copie = v;
    for(int i(0); i<dim; i++)
        copie.coord[i] = copie.coord[i] / (coord[i]);
    return copie;
}

template<typename T, unsigned int dim>
Vector<T,dim> Vector<T,dim>::operator*(T s) const
{
    Vector copie;
    for(int i(0); i<dim; i++)
        copie.coord[i] = s * (coord[i]);
    return copie;
}

template<typename T, unsigned int dim>
Vector<T,dim> Vector<T,dim>::operator/(T s) const
{
    Vector copie;
    for(int i(0); i<dim; i++)
        copie.coord[i] = (coord[i])/ (s);
    return copie;
}

template<typename T, unsigned int dim>
bool Vector<T,dim>::operator==(const Vector& v) const
{
    for(int i(0); i<dim; i++)
    {
        if(coord[i] != v.coord[i])
            return false;
    }
    return true;
}

template<typename T, unsigned int dim>
bool Vector<T,dim>::operator!=(const Vector& v) const
{
    for(int i(0); i<dim; i++)
    {
        if(coord[i] != v.coord[i])
            return true;
    }
    return false;
}

template<typename T, unsigned int dim>
Vector<T,dim>& Vector<T,dim>::operator+=(const Vector& v)
{
    for(int i(0); i<dim; i++)
        coord[i] += v.coord[i];
    return *this;
}

template<typename T, unsigned int dim>
Vector<T,dim>& Vector<T,dim>::operator-=(const Vector& v)
{
    for(int i(0); i<dim; i++)
        coord[i] -= v.coord[i];
    return *this;
}

template<typename T, unsigned int dim>
Vector<T,dim>& Vector<T,dim>::operator*=(const Vector& v)
{
    for(int i(0); i<dim; i++)
        coord[i] *= v.coord[i];
    return *this;
}

template<typename T, unsigned int dim>
Vector<T,dim>& Vector<T,dim>::operator/=(const Vector& v)
{
    for(int i(0); i<dim; i++)
        coord[i] /= v.coord[i];
    return *this;
}

template<typename T, unsigned int dim>
Vector<T,dim>& Vector<T,dim>::operator*=(T s)
{
    for(int i(0); i<dim; i++)
        coord[i] *= s;
    return *this;
}

template<typename T, unsigned int dim>
Vector<T,dim>& Vector<T,dim>::operator/=(T s)
{
    for(int i(0); i<dim; i++)
        coord[i] /= s;
    return *this;
}

template<typename T, unsigned int dim>
T Vector<T,dim>::norm(void) const
{
    T dis = 0;
    for(int i(0); i<dim; i++)
        dis += (coord[i]*coord[i]);
    return  sqrt(dis);
}

template<typename T, unsigned int dim>
void Vector<T,dim>::makeUnitary(void)
{
    T nor = norm();
    for(int i(0); i<dim; i++)
        coord[i] /= nor;
}

template<typename T, unsigned int dim>
Vector<T,dim> Vector<T,dim>::getUnitary(void) const
{
    Vector copie;
    T nor = norm();
    for(int i(0); i<dim; i++)
        copie.coord[i] = coord[i]/nor;
    return copie;
}

template<typename T, unsigned int dim>
T Vector<T,dim>::scalarProd(const Vector& v) const
{
    T sprod(0);
    for(int i(0); i<dim; i++)
        sprod += coord[i]*v.coord[i];
    return sprod;
}

template<typename T, unsigned int dim>
T Vector<T,dim>::distance(const Vector& v) const
{
    T d(0);
    for(int i(0); i<dim; i++)
        d += (coord[i]-v.coord[i]) * (coord[i]-v.coord[i]);
    return sqrt(d);
}

/*TValue Vector::angleX(void) const
{
    TValue theta = acos( x/norm() );
    return theta;
}*/ // a refaire pour les Vect2D uniquement.

template<typename T, unsigned int dim>
T Vector<T,dim>::angle(const Vector& v) const //I think this one is just fine for D-dimension, if cosine is define for the TValue type.
{
    T theta = acos( scalarProd(v)/(norm()*v.norm()) );
    return theta;
}

template<typename T, unsigned int dim>
ostream &operator<<( ostream &flux, Vector<T,dim> const& v)
{
    flux << '(';
    for(int i(0); i<(v.dim-1); i++)
        flux << v.coord[i] << ", ";
    flux << v.coord(dim-1) << ')';
    return flux;
}

template<typename T, unsigned int dim>
Vector<T,dim> operator*(T s, const Vector<T,dim>& v)
{
    Vector<T,dim> vect;
    for(int i(0); i<v.dim; i++)
        vect.coord[i] = s * v.coord[i];
    return vect;
}

template<typename T, unsigned int dim>
Vector<T,dim> operator/(T s, const Vector<T,dim>& v)
{
    Vector<T,dim> vect;
    for(int i(0); i<dim; i++)
        vect.coord[i] = s / v.coord[i];
    return vect;
}


#endif // VECTOR_HPP_INCLUDED
