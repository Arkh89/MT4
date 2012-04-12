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
			jump = new Sound("res/audio/jump.wav");
			coin = new Sound("res/audio/coin.wav");
			soundEngine->setBackgroundSound("res/audio/intro.wav");

			spriteSet = new SpriteSet("./res/img/jokeysmurf.png");
			renderer->setLayer(0,"./res/img/sky.png",0.1);
			renderer->setLayer(1,"./res/img/vegetation.png",0.3);
			renderer->setLayer(2,"./res/img/ground.png",0.5);
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
		static std::vector<SoundSource*> sndSources(NBody,NULL);
		static std::vector<float> scale(NBody,0.15);

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
				sndSources[i] = new SoundSource(bodies[i].getCurPos(t));
			}
		}
		else
		{
			static double tPrevious = World::getTime() ;

			renderer->begin();
			renderer->drawBackground();

			soundEngine->setListenerPosition(-renderer->center);

			double t = World::getTime();

			for(unsigned int i=0; i<bodies.size(); i++)
			{
				Vect2D pos = bodies[i].getCurPos(t);
				Segment s(bodies[i].getCurPos(tPrevious), pos);

				if( s.length()>0 & (s.intersection(s0) | s.intersection(s1) | s.intersection(s2)))
				{
					double s = bodies[i].getSp().norm();
					double x = (static_cast<double>(rand())/static_cast<double>(RAND_MAX)-0.5)*2.0*0.3;
					//cout << bodies[i].getSp() <<endl;
					bodies[i].setNewSpeed(Vect2D(x,s*0.99), t);
					//soundEngine->playSound(sndSources[i], 0); //'jump'
					sndSources[i]->setPosition(pos);
					sndSources[i]->play(*jump);
					//cout << bodies[i].getSp() <<endl;
				}

				if((abs(s.getY1()-s.getY2())<1e-3) && pos.y>0.2)
				{
					sndSources[i]->setPosition(pos);
					sndSources[i]->play(*coin);

					scale[i] = 0.3;
				}

				// Render a smurf as a particle:
				if(bodies[i].getSp().x<0) // facing left
					renderer->draw(*spriteSet,0,bodies[i].getCurPos(t),Vect2D(-scale[i],scale[i]));
				else // facing right
					renderer->draw(*spriteSet,0,bodies[i].getCurPos(t),Vect2D(scale[i],scale[i]));

				if(scale[i]>0.15)
					scale[i] = scale[i]/1.01;
				else
					scale[i] = 0.15;

				// Render a point :
				//renderer->draw(bodies[i].getCurPos(t));
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
