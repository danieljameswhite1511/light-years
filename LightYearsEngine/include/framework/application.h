
#pragma once
#include <SFML/Graphics.hpp>

#include "Core.h"
#include "World.h"

namespace ly
{
	class Application
	{
	public:
		Application(unsigned int windowWidth,unsigned int windowHeight, const std::string title, sf::Uint32 style);
		virtual void Tick(float deltaTime);
		virtual void Render() ;
		void Run();
		template<typename WorldType>
		weak<WorldType> LoadWorld();
		sf::Vector2u GetWindowSize() const;

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();
		sf::RenderWindow mWindow;
		float mTargetFrameRate;
		sf::Clock mTickClock;
		shared<World> currentWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
	};

	template <typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this}};
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();
		return newWorld;
	}
}
