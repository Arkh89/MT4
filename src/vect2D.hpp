#ifndef VECT2D_HPP_INCLUDED
#define VECT2D_HPP_INCLUDED


using namespace std;

typedef float TValue;

	class Vect2D
	{
		public :
		TValue x,y;

		Vect2D(void); // x = 0, y = 0
		Vect2D(int _x, int _y); // x = _x,y = _y
		Vect2D(const Vect2D& v); // x = v.x, y = v.y
		Vect2D(TValue theta); //

		Vect2D& operator+=(const Vect2D &v);
		Vect2D& operator-=(const Vect2D &v);
		Vect2D& operator*=(const Vect2D &v);
		Vect2D& operator/=(const Vect2D &v);
		Vect2D& operator*=(TValue s);
		Vect2D& operator/=(TValue s);

		Vect2D operator+(Vect2D &v) const;
		Vect2D operator-(Vect2D &v) const;
		Vect2D operator-() const;
		Vect2D operator*(Vect2D &v) const;
		Vect2D operator/(Vect2D &v) const;
		Vect2D operator*(TValue s) const;
		Vect2D operator/(TValue s) const;
		bool    operator==(Vect2D &v) const;
		bool    operator!=(Vect2D &v) const;

		void makeUnitary();

		TValue norm() const;
		TValue distance(Vect2D &v) const;
		TValue scalarProd(Vect2D &v) const;
		TValue angle(Vect2D &v) const;
		TValue angleX() const;
		Vect2D getUnitary() const;

		void afficher(std::ostream &flux) const;
	};


        ostream &operator<<( ostream &flux, Vect2D const& v);






#endif // VECT2D_HPP_INCLUDED
