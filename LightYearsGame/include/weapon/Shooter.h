
#pragma once

namespace ly {
	class Actor;
	class Shooter
	{
	public:
		void Shoot();
		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCoolDown() const { return true; }

	protected:
		Shooter(Actor* owningActor);

	private:
		virtual void ShootImpl() = 0;//This makes the class Abstract
	};

	
}