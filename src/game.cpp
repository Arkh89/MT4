#include "game.hpp"
#include "renderer.hpp"

	Game::Game(int& argc, char** argv,int w, int h, int fps)
	 : renderer(NULL), timer(NULL), QApplication(argc,argv)
	{
		renderer = new Renderer(w,h);

		// Create Timer :
		timer = new QTimer;
		timer->setInterval(1.0/fps);

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
		static double i = 0.0;

		Segment s1(0.5,-1,-1,1),
			s2(0,0,0.5f,0.5*sin(i)),
			s3(0.7*cos(i),0.7*sin(i),-0.7*cos(i),-0.7*sin(i));

		renderer->draw(s1);
		renderer->draw(s2);
		renderer->draw(s3);

		renderer->apply();

		i += 0.01;
	}
