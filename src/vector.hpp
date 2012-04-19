#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

	#include <iostream>
	#include <cmath>
	#include <cstdarg>
	#include "exception.hpp"

	using namespace std;

	template<typename TValue, unsigned int d>
	class Vector
	{
		public :
		TValue coord[d];
		static const unsigned int dim=d;
		typedef TValue Type;

		Vector(void); //All coordinates = 0
		//Vector(TValue _x,...);
		Vector(double a1, ...);
		Vector(TValue* dat);
		Vector(const Vector& v);

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
		TValue get(unsigned int i) const;

		void makeUnitary(void);

		TValue norm(void) const;
		TValue distance(const Vector& v) const;
		TValue scalarProd(const Vector& v) const;
		TValue angle(const Vector& v) const;
		Vector getUnitary(void) const;
	};

	template<typename T, unsigned int d>
	Vector<T,d> operator*(T s, const Vector<T,d>& v);

	template<typename T, unsigned int d>
	Vector<T,d> operator/(T s, const Vector<T,d>& v);

	template<typename T, unsigned int d>
	ostream &operator<<( ostream &flux, Vector<T,d> const& v);


	template<typename T, unsigned int d>
	Vector<T,d>::Vector()
	{
		for(int i(0); i<dim; i++)
			coord[i]=0;
	}

	template<typename T, unsigned int d>
	Vector<T,d>::Vector(double a1, ...)
	{
		va_list coordl;
		va_start(coordl, a1);
		coord[0] = static_cast<T>(a1);
		for(int i=1; i<dim; i++)
			coord[i] = static_cast<T>( va_arg(coordl,double) );
		va_end(coordl);
	}

	template<typename T, unsigned int d>
	Vector<T,d>::Vector(T* dat)
	{
		for(int i=0; i<dim; i++)
			coord[i] = dat[i];
	}

	template<typename T, unsigned int d>
	Vector<T,d>::Vector(const Vector<T,d>& v)
	{
		for(int i=0; i<dim; i++)
			coord[i]=v.coord[i];
	}

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
		for(int i=0; i<dim; i++)
			copie.coord[i] = -coord[i];
		return copie;
	}

	template<typename T, unsigned int d>
	Vector<T,d> Vector<T,d>::operator*(const Vector<T,d>& v) const
	{
		Vector copie = v;
		for(int i=0; i<dim; i++)
			copie.coord[i] = copie.coord[i] * (coord[i]);
		return copie;
	}

	template<typename T, unsigned int d>
	Vector<T,d> Vector<T,d>::operator/(const Vector<T,d>& v) const
	{
		Vector copie = v;
		for(int i=0; i<dim; i++)
			copie.coord[i] = copie.coord[i] / (coord[i]);
		return copie;
	}

	template<typename T, unsigned int d>
	Vector<T,d> Vector<T,d>::operator*(T s) const
	{
		Vector copie;
		for(int i=0; i<dim; i++)
			copie.coord[i] = s * (coord[i]);
		return copie;
	}

	template<typename T, unsigned int d>
	Vector<T,d> Vector<T,d>::operator/(T s) const
	{
		Vector copie;
		for(int i=0; i<dim; i++)
			copie.coord[i] = (coord[i])/ (s);
		return copie;
	}

	template<typename T, unsigned int d>
	bool Vector<T,d>::operator==(const Vector<T,d>& v) const
	{
		for(int i=0; i<dim; i++)
		{
			if(coord[i] != v.coord[i])
				return false;
		}
		return true;
	}

	template<typename T, unsigned int d>
	bool Vector<T,d>::operator!=(const Vector<T,d>& v) const
	{
		for(int i=0; i<dim; i++)
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
	T Vector<T,d>::get(unsigned int i) const
	{
		return coord[i];
	}

	template<typename T, unsigned int d>
	Vector<T,d>& Vector<T,d>::operator+=(const Vector<T,d>& v)
	{
		for(int i=0; i<dim; i++)
			coord[i] += v.coord[i];
		return *this;
	}

	template<typename T, unsigned int d>
	Vector<T,d>& Vector<T,d>::operator-=(const Vector<T,d>& v)
	{
		for(int i=0; i<dim; i++)
			coord[i] -= v.coord[i];
		return *this;
	}

	template<typename T, unsigned int d>
	Vector<T,d>& Vector<T,d>::operator*=(const Vector<T,d>& v)
	{
		for(int i=0; i<dim; i++)
			coord[i] *= v.coord[i];
		return *this;
	}

	template<typename T, unsigned int d>
	Vector<T,d>& Vector<T,d>::operator/=(const Vector<T,d>& v)
	{
		for(int i=0; i<dim; i++)
			coord[i] /= v.coord[i];
		return *this;
	}

	template<typename T, unsigned int d>
	Vector<T,d>& Vector<T,d>::operator*=(T s)
	{
		for(int i=0; i<dim; i++)
			coord[i] *= s;
		return *this;
	}

	template<typename T, unsigned int d>
	Vector<T,d>& Vector<T,d>::operator/=(T s)
	{
		for(int i=0; i<dim; i++)
			coord[i] /= s;
		return *this;
	}

	template<typename T, unsigned int d>
	T Vector<T,d>::norm(void) const
	{
		T dis = 0;
		for(int i=0; i<dim; i++)
			dis += (coord[i]*coord[i]);
		return  sqrt(dis);
	}

	template<typename T, unsigned int d>
	void Vector<T,d>::makeUnitary(void)
	{
		T nor = norm();
		for(int i=0; i<dim; i++)
			coord[i] /= nor;
	}

	template<typename T, unsigned int d>
	Vector<T,d> Vector<T,d>::getUnitary(void) const
	{
		Vector copie;
		T nor = norm();
		for(int i=0; i<dim; i++)
			copie.coord[i] = coord[i]/nor;
		return copie;
	}

	template<typename T, unsigned int d>
	T Vector<T,d>::scalarProd(const Vector<T,d>& v) const
	{
		T sprod(0);
		for(int i=0; i<dim; i++)
			sprod += coord[i]*v.coord[i];
		return sprod;
	}

	template<typename T, unsigned int d>
	T Vector<T,d>::distance(const Vector<T,d>& v) const
	{
		T dist=0;
		for(int i=0; i<dim; i++)
			dist += (coord[i]-v.coord[i]) * (coord[i]-v.coord[i]);
		return sqrt(dist);
	}

	template<typename T, unsigned int d>
	T Vector<T,d>::angle(const Vector<T,d>& v) const //I think this one is just fine for D-dimension, if cosine is define for the TValue type.
	{
		T theta = acos( scalarProd(v)/(norm()*v.norm()) );
		return theta;
	}

	template<typename T, unsigned int d>
	ostream& operator<<( ostream &flux, const Vector<T,d>& v)
	{
		flux << '(';
		for(int i=0; i<(v.dim-1); i++)
			flux << v.get(i) << ", ";
		flux << v.get(v.dim-1) << ')';
		return flux;
	}

	template<typename T, unsigned int d>
	Vector<T,d> operator*(T s, const Vector<T,d>& v)
	{
		Vector<T,d> vect;
		for(int i=0; i<v.dim; i++)
			vect.coord[i] = s * v.coord[i];
		return vect;
	}

	template<typename T, unsigned int d>
	Vector<T,d> operator/(T s, const Vector<T,d>& v)
	{
		Vector<T,d> vect;
		for(int i=0; i<v.dim; i++)
			vect.coord[i] = s / v.coord[i];
		return vect;
	}

#endif // VECTOR_HPP_INCLUDED

