
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
}
