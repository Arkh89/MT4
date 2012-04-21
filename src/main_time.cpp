#include "MT4Header.hpp"
#include "world.hpp"
#include <iostream>

int main()
{
    std::cout << "Hello Mary!" << std::endl;
    World w;
    int g = 0;
    double tmax = 500;
    cout  << "ETTTT  VOILAAAA !" << endl;
    double k = World::setTime(100);
    while (World::getTime() < tmax)
    {
        if (g == 1000)
        {
            double s = World::getTime();
            cout << k << "     " << s << endl;
            g = 0;
        }
        g++;
    };
    double s = World::getTime();
    cout << k << "    autre " << s << endl;
    return 0;
}

int main(int argc, char** argv)
{
	Game game(argc,argv,640,480,60);
	return game.exec();
}

int main()
{
	std::cout << "Hello Mary!" << std::endl;


		World w;
		World::setTime(0);
		Vect2D v0(5,5),pos(0,0);
		double t,g(0),tmax(500);

		Body body(pos, v0, 1000, 1,pos);
		Vect2D maxP = body.Body::getCurPos(tmax/1000);
		std::cout << "max"<<maxP<<endl;
		while (World::getTime() < tmax)
		{
			if (g==1000)
			{
				t = World::getTime();
				pos = body.Body::getCurPos(t/1000) ;
				pos/=maxP;
				std::cout << "time: "<<t<<"    position"<< pos << std::endl;
				g=0;
			}
			g++;
		}
}








		static World w;
		static Body body(Vect2D(-300,0), Vect2D(0.5,4), 1000, 1, Vect2D(0,0));
		renderer->draw(body.Body::getCurPos(World::getTime()/1000));
		renderer->apply();



int main()
{
    std::cout << "Hello Mary!" << std::endl;
    World w;
    //int g = 0;
    double tmax = 500;
    for(int i = 0;i<1000;i++)
    {
	cout  << "ETTTT  VOILAAAA !" << endl;
	double k = World::setTime();
	while (World::getTime() < tmax){};
	double s = World::getTime();
	cout << k << "    autre " << s << endl;
    }
    return 0;
}

int main(int argc, char** argv)
{
	Game game(argc,argv,640,480,60);
	return game.exec();
}
int main()
{
	Vect2D v(2,2);
	Segment s(1,0,0,1), s2(0,0,2,2);
	double x,y;
	cout<<v<<endl;
	cout<<s.intersection(s2,x,y)<<endl;
	cout<<x<<endl;
	cout<<y<<endl;
}
