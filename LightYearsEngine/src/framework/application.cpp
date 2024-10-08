
#include <framework/Application.h>
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{

	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string title, sf::Uint32 style)
			:mWindow{ sf::VideoMode(windowWidth, windowHeight), title, style }
			, mTargetFrameRate{ 60.f }
			, mTickClock{}
			, currentWorld{ nullptr }
			, mCleanCycleClock{}
			, mCleanCycleInterval(2.f)
	{
	}
	
	void Application::Run()
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

			accumulatedTime += mTickClock.restart().asSeconds();

			if(accumulatedTime >= targetDeltaTime){
				TickInternal(accumulatedTime);
				accumulatedTime -= targetDeltaTime;
				RenderInternal();
			}
		}
	}


	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
		if(currentWorld){
			//currentWorld->BeginPlayInternal();
			currentWorld->TickInternal(deltaTime);
		}

		if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval){
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			if(currentWorld) {
				currentWorld->CleanCycle();
			}
		}
	}

	void Application::Tick(float deltaTime)
	{
		//LOG("Frame rate is %f", 1.f / deltaTime);
	}

	void Application::RenderInternal()
	{
		mWindow.clear();
		Render();
		mWindow.display();
	}

	void Application::Render()
	{
		currentWorld -> render(mWindow);


		/*sf::RectangleShape rect{ sf::Vector2f{100, 100} };
		rect.setFillColor(sf::Color::Blue);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
		rect.setOrigin(50, 50);
		mWindow.draw(rect);
		*/

	}
}
