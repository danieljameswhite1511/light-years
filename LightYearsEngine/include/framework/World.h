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
		template<typename ActorType>
		weak<ActorType> SpawnActor();
		void render(sf::RenderWindow& window);
		sf::Vector2u GetWindowSize();
	private:
		Application* mOwningApp;
		bool mBeganPlay;
		void BeginPlay();
		void Tick(float deltaTime);
		list<shared<Actor>> mActors;
		list<shared<Actor>> mPendingActors;

	};

	template <typename ActorType>
	weak<ActorType> World::SpawnActor()
	{
		shared<ActorType> newActor{ new ActorType{this} };
		mPendingActors.push_back(newActor);
		return newActor;
	}
}
