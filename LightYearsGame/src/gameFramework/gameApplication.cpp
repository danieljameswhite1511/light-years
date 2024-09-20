#include "gameFramework/GameApplication.h"
#include <iostream>
#include "framework/World.h"
#include "config.h"
#include "framework/AssetManager.h"
#include "PlayerSpaceship/PlayerSpaceship.h"
#include "Spaceship/Spaceship.h"

ly::Application* getApplication()
{
	return new ly::GameApplication{1024, 1440, "Lightyears", 3};
}

namespace ly
{
	GameApplication::GameApplication(unsigned int width,unsigned int height, std::string title, sf::Uint32 style)
	: Application(width, height, title, sf::Style::Titlebar | sf::Style::Close)
	{
		weak<World> newWorld = LoadWorld<World>();
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		
		mSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		

		mSpaceship.lock()->SetActorLocation(sf::Vector2f{ 300.f, 490.f });
		
		mSpaceship.lock()->SetActorRotation(0);

		//mSpaceship.lock()->SetVelocity(sf::Vector2f{ 0.f, 200.f });
		
		


		counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;

		if(counter > 10)
		{
			if(!mSpaceship.expired())
			{
				//mSpaceship.lock()->Destroy();
			}
			
		}

		if(counter > 20)
		{
			if(!mSpaceship.expired())
			{
				//mSpaceship.lock()->Destroy();
			}
			
		}
		Application::Tick(deltaTime);
	}
}
