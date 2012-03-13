#ifndef BODY_HPP_INCLUDED
#define BODY_HPP_INCLUDED
#include "vect2D.hpp"

using namespace std;


class Body
{
	public:

		Body(void);
		Body(Vect2D pos0, double _m, double _k);
		Body(Vect2D pos0, Vect2D v0, double _m, double _k);
		~Body(void);

		Vect2D trajectory(double t);
		Vect2D getCurPos(double t);

		static void setGrav(double gNew); // Pour redéfinir la constante de gravitation => Possibilité de gameplay

	private:
		Vect2D pos,v,R; // Position & Speed
		double m,k; // Mass & friction coefficient
		static double gN; // Gravitation constant 9,81 m.s-2
};

#endif // BODY_HPP_INCLUDED
