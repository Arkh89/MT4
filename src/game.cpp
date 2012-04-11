#include "game.hpp"
#include "renderer.hpp"
#include "body.hpp"
#include "world.hpp"
#include "keyLayout.hpp"
#include "soundEngine.hpp"

	Game::Game(int& argc, char** argv,int w, int h, int fps)
	 : renderer(NULL), keyLayout(NULL), timer(NULL), spriteSet(NULL), QApplication(argc,argv)
	{
		setApplicationName("MT4");

		renderer 	= new Renderer(w,h);
		keyLayout 	= new KeyLayout(renderer);
		soundEngine 	= new SoundEngine();

		try
		{
			unsigned int s = 0;
			s = soundEngine->loadSound("res/audio/jump.wav");
			s = soundEngine->loadSound("res/audio/intro.wav");
			soundEngine->setBackgroundSound(s);

			spriteSet = new SpriteSet("./res/img/jokeysmurf.png");
			renderer->setLayer(0,"./res/img/sky.png",0.1);
			renderer->setLayer(1,"./res/img/vegetation.png",0.3);
			renderer->setLayer(2,"./res/img/ground.png",0.5);
			//spriteSet = new SpriteSet("./res/img/papa.png");
		}
		catch(std::exception& e)
		{
			std::cout << e.what() << std::endl;
			throw e;
		}
		//spriteSet->declareSprite(0,0,519,600);
		//spriteSet->declareSprite(0,0,269,187);
		spriteSet->declareSprite(0,0,75,75);

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
		delete soundEngine;
		delete keyLayout;
		delete renderer;
		delete timer;
	}

	void Game::update(void)
	{
		const unsigned int NBody = 5;
		static World w;
		static bool init = false;
		static Segment 	s0(-0.7,-0.7,0.7,-0.7),
				s1(-1.0,0.0,-0.7,-0.7),
				s2(0.7,-0.7,1.0,0.0);
		static std::vector<Body> bodies(NBody, Body(Vect2D(0,0), Vect2D(0,0), 100.0, 1, Vect2D(0,0)));
		static std::vector<int> sndSources(NBody, 0);

		// Temporary commands :
		if(keyLayout->justReleased(KeyEscape))
			quit();
		if(keyLayout->pressed(KeyRight))
			renderer->center.x+=0.02/renderer->scale;
		if(keyLayout->pressed(KeyLeft))
			renderer->center.x-=0.02/renderer->scale;
		if(keyLayout->pressed(KeyDown))
			renderer->center.y-=0.02/renderer->scale;
		if(keyLayout->pressed(KeyUp))
			renderer->center.y+=0.02/renderer->scale;
		if(keyLayout->pressed(KeyPlus))
			renderer->scale*=1.05;
		if(keyLayout->pressed(KeyMinus))
			renderer->scale/=1.05;
		if(keyLayout->pressed(KeySpace))
		{
			renderer->center.x = 0.0;
			renderer->center.y = 0.0;
			renderer->scale	   = 1.0;
		}
		if(keyLayout->justPressed(KeyReturn))
			World::switchFreeze();


		if(!init)
		{
			srand(time(NULL));
			init = true;
			double t = World::getTime();
			for(unsigned int i=0; i<bodies.size(); i++)
			{
				double x = (static_cast<double>(rand())/static_cast<double>(RAND_MAX)-0.5)*0.5,
				y = static_cast<double>(rand())/static_cast<double>(RAND_MAX)*5.0+2.0;
				bodies[i].setNewSpeed(Vect2D(x,y), t);
				sndSources[i] = soundEngine->getSource();
			}
		}
		else
		{
			static double tPrevious = World::getTime() ;

			renderer->begin();
			renderer->drawBackground();

			double t = World::getTime();

			for(unsigned int i=0; i<bodies.size(); i++)
			{
				Segment s(bodies[i].getCurPos(tPrevious), bodies[i].getCurPos(t));

				if( s.length()>0 & (s.intersection(s0) | s.intersection(s1) | s.intersection(s2)))
				{
					double s = bodies[i].getSp().norm();
					double x = (static_cast<double>(rand())/static_cast<double>(RAND_MAX)-0.5)*2.0*0.3;
					//cout << bodies[i].getSp() <<endl;
					bodies[i].setNewSpeed(Vect2D(x,s*0.99), t);
					soundEngine->playSound(sndSources[i], 0); //'jump'
					//cout << bodies[i].getSp() <<endl;
				}
				// Render a point :
				//renderer->draw(bodies[i].getCurPos(t));

				// Render a smurf as a particle:
				if(bodies[i].getSp().x<0) // facing left
					renderer->draw(*spriteSet,0,bodies[i].getCurPos(t),Vect2D(-0.15,0.15));
				else // facing right
					renderer->draw(*spriteSet,0,bodies[i].getCurPos(t),Vect2D(0.15,0.15));
			}
			tPrevious = t;
		}

		// Unbind current smurf texture
		SpriteSet::unbind();

		renderer->draw(s0);
		renderer->draw(s1);
		renderer->draw(s2);
		//renderer->draw(*spriteSet,0,Vect2D(0.0,0.0),Vect2D(1.5,1.0));
		//renderer->draw(*spriteSet,0,Vect2D(-0.5,0.5),Vect2D(0.7,0.5));
		//renderer->draw(*spriteSet,1,Vect2D(0.5,0.5),Vect2D(0.7,0.5));
		//SpriteSet::unbind();

		renderer->end();
	}
