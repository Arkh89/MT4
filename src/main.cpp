#include "MT4Header.hpp"

int main(int argc, char** argv)
{
	Game game(argc,argv,640,480,60);
	return game.exec();
}
