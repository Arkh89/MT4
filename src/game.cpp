#include "game.hpp"
#include "renderer.hpp"
#include "body.hpp"
#include "world.hpp"
#include "keyLayout.hpp"

	Game::Game(int& argc, char** argv,int w, int h, int fps)
	 : renderer(NULL), keyLayout(NULL), timer(NULL), QApplication(argc,argv)
	{
		renderer = new Renderer(w,h);
		keyLayout = new KeyLayout(renderer);

		// Create Timer :
		timer = new QTimer;
		timer->setInterval(1000.0/fps);

		// Connect event on timer
		connect(timer, SIGNAL(timeout()),this, SLOT(update()));

		// Start timer
		timer->start();

		// Connect keyboard input :
		connect(renderer, SIGNAL(keyPress(QKeyEvent*)), keyLayout, SLOT(keyPress(QKeyEvent*)));
		connect(renderer, SIGNAL(keyRelease(QKeyEvent*)), keyLayout, SLOT(keyRelease(QKeyEvent*)));
	}

	Game::~Game(void)
	{
		disconnect(renderer, SIGNAL(keyPress(QKeyEvent*)), keyLayout, SLOT(keyPress(QKeyEvent*)));
		disconnect(renderer, SIGNAL(keyRelease(QKeyEvent*)), keyLayout, SLOT(keyRelease(QKeyEvent*)));
		delete keyLayout;
		delete renderer;
		delete timer;
	}

	void Game::update(void)
	{
		static World w;
		static bool init = false;
		static Segment 	s0(-0.7,-0.7,0.7,-0.7),
				s1(-1.0,0.0,-0.7,-0.7),
				s2(0.7,-0.7,1.0,0.0);

		// Temp :
		if(keyLayout->justReleased(KeyEscape))
			quit();
		if(keyLayout->pressed(KeyRight))
			renderer->center.x+=0.02;
		if(keyLayout->pressed(KeyLeft))
			renderer->center.x-=0.02;
		if(keyLayout->pressed(KeyDown))
			renderer->center.y-=0.02;
		if(keyLayout->pressed(KeyUp))
			renderer->center.y+=0.02;
		if(keyLayout->pressed(KeySpace))
		{
			renderer->center.x = 0.0;
			renderer->center.y = 0.0;
		}

		static std::vector<Body> bodies(1000, Body(Vect2D(0,0), Vect2D(0,0), 100.0, 1, Vect2D(0,0)));
		if(!init)
		{
			srand(time(NULL));
			init = true;
			double t = World::getTime();
			for(unsigned int i=0; i<bodies.size(); i++)
			{
				double x = (static_cast<double>(rand())/static_cast<double>(RAND_MAX)-0.5)*2.0,
				y = static_cast<double>(rand())/static_cast<double>(RAND_MAX)*10.0;
				bodies[i].setNewSpeed(Vect2D(x,y), t);
			}
		}
		else
		{




			static double tPrevious = World::getTime() ;

			double t = World::getTime();

			    for(unsigned int i=0; i<bodies.size(); i++)
			    {

				Segment s(bodies[i].getPos(),bodies[i].getCurPos(t));
				if (s.intersection(s0) | s.intersection(s1) | s.intersection(s2))
				{
				    Vect2D sp = bodies[i].getSp();
				    cout << bodies[i].getSp() <<endl;
				    bodies[i].setNewSpeed(-sp, t);
				    cout << bodies[i].getSp() <<endl;
				}
				renderer->draw(bodies[i].getCurPos(t));
			    }
			    tPrevious = t;
		}

		renderer->draw(s0);
		renderer->draw(s1);
		renderer->draw(s2);

		renderer->apply();
	}
