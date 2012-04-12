#ifndef BODY_HPP_INCLUDED
#define BODY_HPP_INCLUDED
#include "vect2D.hpp"

using namespace std;


class Body
{
	public:

		Body(void);
		Body(const Vect2D& pos0, double _m, double _k);
		Body(const Vect2D& pos0, const Vect2D& v0, double _m, double _k);
		Body(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, const Vect2D& _R);
		Body(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, const Vect2D& _R, double _tI);
		~Body(void);

		Vect2D trajectory(double t);
		Vect2D getCurPos(double t);
		Vect2D getSp(void);
		Vect2D getPos(void);

		void setNewSpeed(Vect2D s,double ti);
		void teleport(const Vect2D& p,double ti);

        static void setGrav(Vect2D gNew); // To define again the gravitation constant => extended gameplay possibilities

	private:
		Vect2D pos,v,R; // Position & Speed
		double m,k,tI; // Mass & friction coefficient & Initial time
		static Vect2D gN; // Gravitation constant 9,81 m.s-2
};

#endif // BODY_HPP_INCLUDED
