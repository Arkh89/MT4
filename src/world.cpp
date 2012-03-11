#include "world.hpp"
#include <ctime>
#include <stdio.h>

World(void)
 : time0(clock()), time(0)
{ }


int World::getTime()
{
	return time= 1000 * (clock() - time0)/CLOCKS_PER_SEC;
}

// BORDEL Pourquoi ?

//Mon main
//#include "MT4Header.hpp"
//#include "world.hpp"
//#include <stdio.h>
//#include <ctime>

//int main()
//{
//	std::cout << "Hello Mary!" << std::endl;
//	World w();
//	int s = w.getTime();
//	cout << s <<endl;
//	return 0;
//}


// Et là il me renvoit erreur: request for member ‘getTime’ in ‘w’, which is of non-class type ‘World()’ => Mais SIIIII w est un World, non ?
// Enfin voilà ça me saoule ça fait deux jours maintenant... donc j'en ai marre => HEEELP ! Merci
