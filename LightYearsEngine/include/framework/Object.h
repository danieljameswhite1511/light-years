#pragma once
#include <memory>

#include "Core.h"

namespace ly
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();
		bool IsPendingDestroy() const { return mIsPendingDestruction; }
		virtual void Destroy();
		weak<Object> GetWeakRef();
		weak<const Object> GetWeakRef() const;
	private:
		bool mIsPendingDestruction;
	};

	
}
