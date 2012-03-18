#include "game.hpp"
#include "renderer.hpp"
#include "body.hpp"
#include "world.hpp"

	Game::Game(int& argc, char** argv,int w, int h, int fps)
	 : renderer(NULL), timer(NULL), QApplication(argc,argv)
	{
		renderer = new Renderer(w,h);

		// Create Timer :
		timer = new QTimer;
		timer->setInterval(1000.0/fps);

		// Connect event on timer
		connect(timer, SIGNAL(timeout()),this, SLOT(update()));

		// Start timer
		timer->start();
	}

	Game::~Game(void)
	{
		delete renderer;
		delete timer;
	}

	void Game::update(void)
	{
		static World w;
		static bool init = false;


		static std::vector<Body> bodies(1000, Body(Vect2D(0,0), Vect2D(0,0), 100.0, 1, Vect2D(0,0)));
		if(!init)
		{
			World::setTime();
			init = true;
			for(int i=0; i<bodies.size(); i++)
			{
				double x = static_cast<double>(rand())/static_cast<double>(RAND_MAX)*3.0-1.0,
				y = static_cast<double>(rand())/static_cast<double>(RAND_MAX)*15.0-1.0;
				bodies[i].setNewSpeed(Vect2D(x,y), World::getTime()/1000.0);
			}
		}
		else
		{
			double t = World::getTime();
			for(int i=0; i<bodies.size(); i++)
			renderer->draw(bodies[i].getCurPos(t/1000.0));
		}
		renderer->apply();
	}
