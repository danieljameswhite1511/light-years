#pragma once
namespace ly
{
	class Object
	{
	public:
		Object();
		virtual ~Object();
		bool IsPendingDestroy() const { return mIsPendingDestruction; }
		void Destroy();
	private:
		bool mIsPendingDestruction;
	};

	
}
