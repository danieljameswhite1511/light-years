
#include "Spaceship/Spaceship.h"

#include <functional>

#include "framework/MathUtility.h"

namespace ly {

	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{owningWorld, texturePath}
	, mVelocity{}
	, mHealthComponent{100.f, 100.f}
	, mBlinkColorOffset{255, 0,0}
	, mBlinkDuration{0.2f}
	, mBlinkTime(0.f)
	{
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVel)
	{
		mVelocity = newVel;
	}



	void Spaceship::Tick(float deltaTime)
	{
		
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);

	}

	void Spaceship::Shoot()
	{
	}

	void Spaceship:: BeginPlay() {

		LOG("Playing Spaceship");
		Actor::BeginPlay();
		SetEnablePhysics(true);
		mHealthComponent.onHealthChanged.BindToAction<>(GetWeakRef(), &Spaceship::OnHealthChanged);
		mHealthComponent.onTakenDamages.BindToAction<>(GetWeakRef(), &Spaceship::OnTakenDamage);
		mHealthComponent.onHealthEmpty.BindToAction<>(GetWeakRef(), &Spaceship::Explode);

		std::function<void(float)> func = [](float var) {
			LOG("the value is %f", var);
		};

		func(3);
	}

	void Spaceship::OnHealthChanged(float amount, float health, float maxHealth) {
		LOG("Health Changed by %f and is now %f/%f", amount, health, maxHealth);
	}

	void Spaceship::OnTakenDamage(float amount, float health, float maxHealth) {
		Blink();
	}

	void Spaceship::Explode() {
		Destroy();
	}

	void Spaceship::ApplyDamage(float damage) {
		mHealthComponent.changeHealth(-damage);

		Actor::ApplyDamage(damage);
	}

	void Spaceship::Blink() {

		if(mBlinkTime == 0.f) {
			mBlinkTime = mBlinkDuration;
		}
	}

	void Spaceship::UpdateBlink(float deltaTime) {
		if(mBlinkTime > 0.f) {
			mBlinkTime -= deltaTime;
			mBlinkTime = mBlinkTime > 0.f ? mBlinkTime : 0.f;
			sf::Color color = sf::Color::White;
			GetSprite().setColor(LerpColor(color, mBlinkColorOffset, mBlinkTime));
		}

	}
}
