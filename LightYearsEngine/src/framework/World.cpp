
#pragma once

#include "framework/World.h"
#include "framework/Application.h"
#include "framework/Core.h"

namespace ly
{
	World::World(Application* owningApp)
		:mOwningApp{ owningApp }
	, mBeganPlay{false}
	, mActors{}
	, mPendingActors{}
	{
	}

	void World::BeginPlayInternal()
	{
		if(!mBeganPlay)
		{
			mBeganPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
		}
		mPendingActors.clear();

		//benefit of uing iterator is has the erase function that enumerates
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if(iter->get()->IsPendingDestruction())
			{
				iter = mActors.erase(iter);
			}
			else
			{
				iter->get()->TickInternal(deltaTime);
				++iter;
			}
		}
		
		Tick(deltaTime);
	}

	void World::render(sf::RenderWindow& window){
		for (auto& actor : mActors)
		{
			actor->render(window);
		}
	}

	sf::Vector2u World::GetWindowSize()
	{
		return mOwningApp->GetWindowSize();
	}


	void World::BeginPlay()
	{
		//LOG("Play has begun");

	}

	void World::Tick(float deltaTime)
	{
		//LOG("Framerate %f", 1.f / deltaTime);
	}
}
