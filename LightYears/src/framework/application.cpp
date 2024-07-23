
#include <framework/application.h>


namespace ly
{
	application::application()
		:window{sf::VideoMode(1024, 1440), "Light Years"}
	{

	}

	void application::run()
	{
		while (window.isOpen())
		{
			sf::Event window_event;

			while (window.pollEvent(window_event))
			{
				if (window_event.type == sf::Event::Closed)
				{
					window.close();
				}
			}

		}
	}
}
