#include "weapon/Bullet.h"
#include "framework/Actor.h"

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		:Actor{world, texturePath}
		,mOwner{owner}	,mSpeed{speed}, mDamage{damage}

	{
	}

	void Bullet::SetSpeed(float newSpeed)
	{
		mSpeed = newSpeed;
	}

	void Bullet::SetDamage(float newDamage)
	{
		mDamage = newDamage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
		if(IsActorOutOfWindowBounds()) {
			Destroy();
		}

	}

	void Bullet::BeginPlay() {
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Bullet::Move(float deltaTime)
	{
		sf::Vector2f actorForwardDirection = GetActorForwardDirection();

		actorForwardDirection.x *= -1;
		actorForwardDirection.y *= -1;

		AddActorLocationOffset(actorForwardDirection * mSpeed * deltaTime);
	}

	
}
