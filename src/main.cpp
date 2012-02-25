#include "MT4Header.hpp"

int main(int argc, char** argv)
{
	sf::Window App(sf::VideoMode(800, 600, 32), "SFML Window");

	bool Running = true;
	while(Running)
	{

		sf::Event Event;
		while (App.GetEvent(Event))
		{
			// Window closed
			if (Event.Type == sf::Event::Closed)
				Running = false;

			// Escape key pressed
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				Running = false;
		}
		App.Display();
	}

	return 0;
}
