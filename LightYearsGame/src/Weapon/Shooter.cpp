
#include "weapon/Shooter.h"

namespace ly {
	void Shooter::Shoot()
	{
		if(CanShoot() && !IsOnCoolDown())
		{
			ShootImpl();
		}
	}

	Shooter::Shooter(Actor* owner)
		: mOwner{owner}
	{

	}
}
