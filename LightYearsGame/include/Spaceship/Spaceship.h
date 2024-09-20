
#pragma once
#include "framework/Actor.h"



namespace ly {
	class Spaceship : public Actor {
		
	public:
		Spaceship(World* owningWorld, const std::string& texturePath= "" );
		void SetVelocity(const sf::Vector2f& newVel);
		sf::Vector2f GetVelocity() const { return mVelocity; }
		virtual void Tick(float deltaTime) override;
	
	private:
		
		sf::Vector2f mVelocity;

	};
}