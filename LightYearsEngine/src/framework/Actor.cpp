#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
	Actor::Actor(World* owningWorld,const std::string& texturePath):
		  mOwningWorld{owningWorld}
		, mSprite{}
		, mTexture{}
	{
		setTexture(texturePath);
	}	

	void Actor::BeginPlayInternal()
	{
		if(!mHasBegunPlay)
		{
			mHasBegunPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
		LOG("Actor has begun play");
	}

	void Actor::Tick(float deltaTime)
	{
		//LOG("Actor ticking");
	}

	void Actor::TickInternal(float deltaTime)
	{
		if(!IsPendingDestruction())
		{
			Tick(deltaTime);
		}
	}

	Actor::~Actor()
	{
		//LOG("Actor destroyed");
	}

	void Actor::setTexture(std::string path)
	{
	
		mTexture = AssetManager::Get().LoadTexture(path);
		if(!mTexture) return;
		mSprite.setTexture(*mTexture);

	
		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;

		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
		CentrePivot();
	}

	void Actor::render(sf::RenderWindow& window)
	{
		if(IsPendingDestruction()) return;
			 
		window.draw(mSprite);
	}

	void Actor::SetActorLocation(sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
	}

	void Actor::SetActorRotation(float newRotation)
	{
		mSprite.setRotation(newRotation);
	}

	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}


	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		 SetActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorRotationOffset(const float offsetAmt)
	{
		SetActorRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return  RotationToVector(GetActorRotation() + 90.f);
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const{
		return mSprite.getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningWorld->GetWindowSize();
	}

	bool Actor::IsActorOutOfWindowBounds() const {
		float windowWidth = mOwningWorld->GetWindowSize().x;
		float windowHeight = mOwningWorld->GetWindowSize().y;

		float actorWidth = GetActorGlobalBounds().width;
		float actorHeight = GetActorGlobalBounds().height;

		sf::Vector2f actorPosition = GetActorLocation();
		if(actorPosition.x < -actorWidth) {
			return true;
		}
		if(actorPosition.x > windowWidth + actorWidth) {
			return true;
		}
		if(actorPosition.y < -actorHeight) {
			return true;
		}
		if(actorPosition.y > windowHeight + actorHeight) {
			return true;
		}

		return false;
	}


	void Actor::CentrePivot(){
		
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(sf::Vector2f{bound.height/2.f,bound.width/2.f});
	}
}
