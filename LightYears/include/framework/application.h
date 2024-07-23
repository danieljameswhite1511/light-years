
#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
	class application
	{
	public:
		application();
		void run();


	private: 
		sf::RenderWindow window;
	};
	
}