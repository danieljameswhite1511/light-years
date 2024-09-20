
#pragma once
#include "Spaceship/Spaceship.h"
namespace ly {
	class PlayerSpaceship : public Spaceship {
	public:
		PlayerSpaceship(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime) override;
		void SetSpeed(float speed) { mSpeed = speed; };
		float GetSpeed() const { return mSpeed; };

	private:
		void HandleInput();
		void NormalizeInput();
		void ConsumeInput(float deltaTime);
		void ClampInputOnEdge();
		sf::Vector2f mMoveInput;
		float mSpeed;
	};
}