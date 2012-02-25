#include "MT4Header.hpp"

int main(int argc, char** argv)
{
	sf::Window app(sf::VideoMode(640, 480, 32), "M4T Window");

	bool running = true;

	while(running)
	{
		sf::Event event;

		// While there is an event to process
		while(app.GetEvent(event))
		{
			// If the window is closed : stop
			if (event.Type == sf::Event::Closed)
				running = false;

			// If the key escape is pressed : stop
			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
				running = false;
		}

		// Display the window
		app.Display();
	}

	return 0;
}
