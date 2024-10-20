#include "gameFramework/GameApplication.h"
#include <iostream>
#include "framework/World.h"
#include "config.h"
#include "framework/AssetManager.h"
#include "PlayerSpaceship/PlayerSpaceship.h"
#include "Spaceship/Spaceship.h"

ly::Application* getApplication()
{
	return new ly::GameApplication{600, 980, "Lightyears", 3};
}

namespace ly
{
	GameApplication::GameApplication(unsigned int width,unsigned int height, std::string title, sf::Uint32 style)
	: Application(width, height, title, sf::Style::Titlebar | sf::Style::Close)
	{
		weak<World> newWorld = LoadWorld<World>();
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		
		mSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();

		sf::Vector2f position{300.f, 490.f};

		mSpaceship.lock()->SetActorLocation(position);
		
		mSpaceship.lock()->SetActorRotation(90);

		//mSpaceship.lock()->SetVelocity(sf::Vector2f{ 0.f, 200.f });

		weak<Spaceship> testSpaceShip = newWorld.lock()->SpawnActor<Spaceship>("SpaceShooterRedux/PNG/playerShip1_blue.png");
		//testSpaceShip.lock()->SetTexture();
		sf::Vector2f position2{100.f, 50.f};
		testSpaceShip.lock()->SetActorLocation(position2);

		


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
