
#pragma once
#include "framework/Actor.h"
#include "GamePlay/HealthComponent.h"

namespace ly {
	class Spaceship : public Actor {
		
	public:
		Spaceship(World* owningWorld, const std::string& texturePath= "" );
		void SetVelocity(const sf::Vector2f& newVel);
		sf::Vector2f GetVelocity() const { return mVelocity; }
		virtual void Tick(float deltaTime) override;
		virtual void Shoot();
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float damage) override;

	private:
		void Blink();
		void UpdateBlink(float deltaTime);
		virtual void OnHealthChanged(float amount, float health, float maxHealth);
		virtual void OnTakenDamage(float amount, float health, float maxHealth);
		virtual void Explode();
		sf::Vector2f mVelocity;
		HealthComponent mHealthComponent;
		float mBlinkTime;
		float mBlinkDuration;
		sf::Color mBlinkColorOffset;

	};
}
