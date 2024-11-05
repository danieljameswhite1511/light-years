
#pragma once
#include "framework/Object.h"

#include "framework/Core.h"

namespace ly
{
	Object::Object()
		:mIsPendingDestruction{false}
	{
	}

	Object::~Object()
	{
		LOG("Object destroyed");
	}

	void Object::Destroy()
	{
		mIsPendingDestruction = true;
	}

	weak<Object> Object::GetWeakRef()  {
		return weak_from_this();
	}
	weak<const Object> Object::GetWeakRef() const {
		return weak_from_this();
	}
}
