
#include <iostream>
#include <framework/application.h>


namespace ly
{
	application::application()
		:mWindow{sf::VideoMode(1024, 1440), "Light Years"}
		, mTargetFrameRate{60.f}
		, mTickClock{}
	{

	}

	
	void application::run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFrameRate;
		while (mWindow.isOpen())
		{
			sf::Event window_event;

			while (mWindow.pollEvent(window_event))
			{
				if (window_event.type == sf::Event::Closed)
				{
					mWindow.close();
				}
			}

			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += mTickClock.restart().asSeconds();

			if(accumulatedTime >= targetDeltaTime)
			{
				
				tickInternal(accumulatedTime);
				accumulatedTime -= targetDeltaTime;
				renderInternal();
				
			}

			//std::cout<< "Real time" << 1.f / frameDeltaTime << "\n";
			
		}
	}

	void application::tickInternal(float deltaTime)
	{
		tick(deltaTime);
	}

	void application::tick(float deltaTime)
	{
		std::cout << "delta time" << deltaTime << "\n";
		std::cout << 1.f / deltaTime << "\n";

	}

	void application::renderInternal()
	{
		mWindow.clear();

		render();
		
		mWindow.display();
	}

	void application::render()
	{

		sf::RectangleShape rect{ sf::Vector2f{100, 100} };
		rect.setFillColor(sf::Color::Blue);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
		rect.setOrigin(50, 50);
		mWindow.draw(rect);

	}
}
