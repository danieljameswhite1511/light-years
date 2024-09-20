#pragma once
#include <framework/Application.h>



namespace ly
{
	class Actor;
	class Spaceship;

	class GameApplication : public Application
	{
	public:
		
		GameApplication(unsigned int width, unsigned int height, std::string title, sf::Uint32 style);
		virtual void Tick(float deltaTime) override;
		
		

	private:
		float counter;
		weak<Spaceship> mSpaceship;
		
	};
}


