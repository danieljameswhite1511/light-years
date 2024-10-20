
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

		for (auto iter = mActors.begin(); iter != mActors.end();){
			iter->get()->TickInternal(deltaTime);
			++iter;
		}
		
		Tick(deltaTime);
	}

	void World::render(sf::RenderWindow& window){
		for (auto& actor : mActors)
		{
			actor->Render(window);
		}
	}

	sf::Vector2u World::GetWindowSize()
	{
		return mOwningApp->GetWindowSize();
	}

	void World::CleanCycle() {

		//benefit of using iterator is it has the erase function that enumerates
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if(iter->get()->IsPendingDestruction())
			{
				iter = mActors.erase(iter);
			}
			else
			{
				++iter;
			}
		}
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
