#include "MT4Header.hpp"

int main(int argc, char** argv)
{
	std::cout << "Hello Mary!" << std::endl;

	Game game(argc,argv,640,480,30);

	return game.exec();
}
