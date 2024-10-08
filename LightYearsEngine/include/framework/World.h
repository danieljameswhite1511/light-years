#pragma once
#include "Actor.h"
#include "Core.h"

namespace ly {
	class Application;
	class Actor;
	class World
	{
	public:
		World(Application* applicationOwner);
		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		//has variadic template params
		template<typename ActorType, typename... Args>
		weak<ActorType> SpawnActor(Args... args);

		void render(sf::RenderWindow& window);
		sf::Vector2u GetWindowSize();
		void CleanCycle();
		Application* mOwningApp;
		bool mBeganPlay;
		void BeginPlay();
		void Tick(float deltaTime);
		list<shared<Actor>> mActors;
		list<shared<Actor>> mPendingActors;

	};

	template <typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...) };
		mPendingActors.push_back(newActor);

		return newActor;
	}
}
