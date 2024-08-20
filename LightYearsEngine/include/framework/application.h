
#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
	class application
	{
	public:
		application();
		void tickInternal(float deltaTime);
		virtual void tick(float deltaTime);
		void renderInternal();
		virtual void render() ;
		void run();

	private: 
		sf::RenderWindow mWindow;
		float mTargetFrameRate;
		sf::Clock mTickClock;
	};
	
}