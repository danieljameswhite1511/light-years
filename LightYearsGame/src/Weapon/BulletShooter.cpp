#include "weapon/BulletShooter.h"

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "weapon/Bullet.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime )
		:Shooter{owner}
	, mCooldownClock{}
	, mCooldownTime{cooldownTime}

	{
	}

	bool BulletShooter::IsOnCoolDown() const
	{
		if(mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
		{
			return false;
		}

		return true;
	}

	void BulletShooter::ShootImpl()
	{
		mCooldownClock.restart();
		LOG("Shooting");

		sf::Vector2f ownerLocation = GetOwner()->GetActorLocation();
		sf::Vector2f bulletStart = sf::Vector2f(ownerLocation.x -35, ownerLocation.y);


		const weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(),"SpaceShooterRedux/PNG/Lasers/laserBlue01.png", 1000.f);
		newBullet.lock()->SetActorLocation(bulletStart);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
	}
}
