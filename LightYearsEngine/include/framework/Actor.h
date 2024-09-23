#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>
#include "Core.h"

namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		
		void BeginPlayInternal();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void TickInternal(float deltaTime);
		virtual ~Actor();
		void setTexture(std::string path);
		void render(sf::RenderWindow& window);
		void SetActorLocation(sf::Vector2f& newLocation);
		void SetActorRotation(float newRotation);
		float GetActorRotation();

		sf::Vector2f GetActorLocation() const;

		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(const float offsetAmt);
		sf::Vector2f GetActorForwardDirection();
		sf::Vector2f GetActorRightDirection();
		sf::Vector2u GetWindowSize() const;
		World* GetWorld() const { return  mOwningWorld; }


	private:
		World* mOwningWorld;
		bool mHasBegunPlay;
		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
		void CentrePivot();

	};

	
}
