#include "game.hpp"
#include "renderer.hpp"
#include "body.hpp"
#include "world.hpp"
#include "keyLayout.hpp"
#include "soundEngine.hpp"
#include "color.hpp"
#include "network.hpp"

	Game::Game(int& argc, char** argv,int w, int h, int fps)
	 : renderer(NULL), keyLayout(NULL), timer(NULL), server(NULL), connection(NULL), spriteSet(NULL), QApplication(argc,argv)
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
                        soundEngine->setBackgroundSound("res/audio/smurfs.wav");

			//spriteSet = new SpriteSet("./res/img/minisprite.jpg");
			//renderer->setLayer(0,"./res/img/fond.jpg",0.1);
			//renderer->setLayer(1,"./res/img/vegetation.png",0.3);
			//renderer->setLayer(2,"./res/img/ground.png",0.5);

			spriteSet = new SpriteSet("./res/img/papa.png");
			renderer->setLayer(0,"./res/img/papa.png",0.1);
			renderer->setLayer(1,"./res/img/papa.png",0.3);
			renderer->setLayer(2,"./res/img/papa.png",0.5);

			// Network :
			if(argc>=2)
			{
				std::string arg = argv[1];
				std::cout << "Argument : " << arg << std::endl;
				if(arg=="-server") //server
				{
					std::cout << "Creating server..." << std::endl;
					server = new Server(1220);
				}
				else if(arg=="-client")
				{
					std::cout << "Creating connection to server..." << std::endl;
					connection = new Connection(1221,QHostAddress(QString("100.0.0.1")),1220);
					connection->sendMessage("Hello World!");
				}
				else
					std::cout << "Network role : " << argv[1] << "unknown." << std::endl;
			}
			else
				std::cout << "No Network role defined." << std::endl;
			// Working on local network :
			/*server = new Server(1221);
			connection = new Connection(1221,QHostAddress(QString("127.0.0.1")),1221);
			connection->sendMessage("Hello World!");*/
		}
		catch(std::exception& e)
		{
			std::cout << e.what() << std::endl;
			throw e;
		}
		//spriteSet->declareSprite(0,0,519,600);
		//spriteSet->declareSprite(0,0,269,187);
		spriteSet->declareSprite(0,0,97,190);

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

	int icol = 0;
	void Game::update(void)
	{
		const unsigned int NBody = 5;
		static World w;
		static bool init = false, realRendering=true;
		static Segment 	s0(-0.7,-0.7,0.7,-0.7),
				s1(-1.0,0.0,-0.7,-0.7),
				s2(0.7,-0.7,1.0,0.0),
				s3(1.0,0.0,0.0,1.0),
				s4(0.0,0.7,-1.0,0.0);
		static std::vector<Body> bodies(NBody, Body(Vect2D(0,0), Vect2D(0,0), 100.0, 5, Vect2D(0,0)));
		static std::vector<SoundSource*> sndSources(NBody,NULL);
		static std::vector<float> scale(NBody,0.15);
		static const Color col(0,255,0,255);
		static const Color newcol(0,0,0,255);


		// Temporary commands :
		if(keyLayout->justReleased(KeyEscape))
			quit();
		if(keyLayout->pressed(KeyRight))
			renderer->center.x()+=0.02/renderer->scale;
		if(keyLayout->pressed(KeyLeft))
			renderer->center.x()-=0.02/renderer->scale;
		if(keyLayout->pressed(KeyDown))
			renderer->center.y()-=0.02/renderer->scale;
		if(keyLayout->pressed(KeyUp))
			renderer->center.y()+=0.02/renderer->scale;
		if(keyLayout->pressed(KeyPlus))
			renderer->scale*=1.05;
		if(keyLayout->pressed(KeyMinus))
			renderer->scale/=1.05;
		if(keyLayout->justPressed(KeySpace))
		{
			renderer->center.x() = 0.0;
			renderer->center.y() = 0.0;
			renderer->scale	   = 1.0;
			realRendering = !realRendering;
		}
		if(keyLayout->justPressed(KeyReturn))
		{
			if(server!=NULL) // This application is the server
				server->broadcast("Time is freezed on the server at : " + to_string(w.getTime()) + ".");
			w.switchFreeze();
		}


		if(!init)
		{
			srand(time(NULL));
			init = true;
			double t = w.getTime();
			for(unsigned int i=0; i<bodies.size(); i++)
			{
				double x = (static_cast<double>(rand())/static_cast<double>(RAND_MAX)-0.5)*0.5,
				y = static_cast<double>(rand())/static_cast<double>(RAND_MAX)*2.0+1.0;
				bodies[i].setNewSpeed(Vect2D(x,y), t);
				sndSources[i] = new SoundSource(bodies[i].getCurPos(t));
			}
			//Body::setGrav(Vect2D(1,8.81));
		}
		else
		{
			static double tPrevious = w.getTime() ;

			renderer->begin();
			renderer->drawBackground();

                        soundEngine->setListenerPosition(-renderer->center);

			double t = w.getTime();
			float a,b;

			for(unsigned int i=0; i<bodies.size(); i++)
			{
				Vect2D pos = bodies[i].getCurPos(t);
				Segment s(bodies[i].getCurPos(tPrevious), pos);

				if(s.length()>1e-3)
					renderer->draw(s);

				if( s.length()>0 & (s.intersection(s0,a,b) | s.intersection(s1,a,b) | s.intersection(s2,a,b) | s.intersection(s3,a,b) | s.intersection(s4,a,b) ))
				{
					double tCol = tPrevious*(1.0-a) + t*a;
					if (s.intersection(s0,a,b)) bodies[i].setNewSpeed(s0.mirror(bodies[i].getCurSp(tCol)), tCol);
					if (s.intersection(s1,a,b)) bodies[i].setNewSpeed(s1.mirror(bodies[i].getCurSp(tCol)), tCol);
					if (s.intersection(s2,a,b)) bodies[i].setNewSpeed(s2.mirror(bodies[i].getCurSp(tCol)), tCol);
					if (s.intersection(s3,a,b)) bodies[i].setNewSpeed(s3.mirror(bodies[i].getCurSp(tCol)), tCol);
					if (s.intersection(s4,a,b)) bodies[i].setNewSpeed(s4.mirror(bodies[i].getCurSp(tCol)), tCol);
					pos = bodies[i].getCurPos(tCol);

                                        sndSources[i]->setPosition(pos);
                                        sndSources[i]->play(*jump);
					//cout << bodies[i].getSp() <<endl;

					if(server!=NULL) // This application is the server
						server->broadcast("There is a collision on the server for body " + to_string(i) + "!");
				}

				if((abs(s.getY1()-s.getY2())<1e-3) && pos.y()>0.2)
				{
                                        sndSources[i]->setPosition(pos);
                                        sndSources[i]->stop();
                                        sndSources[i]->play(*coin);
					scale[i] = 0.3;
				}

				if(pos.y()<-2.0)
				{
					bodies[i].teleport(Vect2D(0,3), t);
					double 	x = (static_cast<double>(rand())/static_cast<double>(RAND_MAX)-0.5)*0.5;
						//y = static_cast<double>(rand())/static_cast<double>(RAND_MAX)*5.0+2.0;*/
					//bodies[i].setNewSpeed(Vect2D(x,y), t);
					bodies[i].setNewSpeed(Vect2D(x,0), t);
				}

				/*if(icol>300)
				{
					Color col=newcol;
				}*/

				// Render a smurf as a particle:
				if(realRendering)
				{
					if(bodies[i].getSp().x()<0) // facing left
						renderer->draw(*spriteSet,0,bodies[i].getCurPos(t),Vect2D(-scale[i],scale[i]));
					else // facing right
						renderer->draw(*spriteSet,0,bodies[i].getCurPos(t),Vect2D(scale[i],scale[i]));
				}
				else
				{
					/*Color c;
					c.R() = 255;
					c.G() = 128;
					c.B() = 64;
					c.A() = 128;*/
					// Render a point :
					renderer->draw(bodies[i].getCurPos(t),col,20);
				}


				if(scale[i]>0.15)
					scale[i] = scale[i]/1.01;
				else
					scale[i] = 0.15;
			}
			tPrevious = t;
			icol++;
		}

		// Unbind current smurf texture
		SpriteSet::unbind();

		renderer->draw(s0);
		renderer->draw(s1);
		renderer->draw(s2);
		renderer->draw(s3);
		renderer->draw(s4);
		//renderer->draw(*spriteSet,0,Vect2D(0.0,0.0),Vect2D(1.5,1.0));
		//renderer->draw(*spriteSet,0,Vect2D(-0.5,0.5),Vect2D(0.7,0.5));
		//renderer->draw(*spriteSet,1,Vect2D(0.5,0.5),Vect2D(0.7,0.5));
		//SpriteSet::unbind();

		renderer->end();
	}

