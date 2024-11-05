#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>
#include "Core.h"

class b2Body;

namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		
		void BeginPlayInternal();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void TickInternal(float deltaTime);
		virtual ~Actor();
		void SetTexture(const std::string &path);
		void Render(sf::RenderWindow& window);
		void SetActorLocation(sf::Vector2f& newLocation);
		void SetActorRotation(float newRotation);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);
		float GetActorRotation() const;
		sf::Vector2f GetActorLocation() const;
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;
		sf::FloatRect GetActorGlobalBounds() const;
		sf::Vector2u GetWindowSize() const;
		World* GetWorld() const { return  mOwningWorld; }
		bool IsActorOutOfWindowBounds() const;
		void SetEnablePhysics(bool enablePhysics);

		virtual void OnBeginOverlap(Actor * actor);
		virtual void OnEndOverlap(Actor * actor);
		virtual void Destroy() override;
		static uint8 GetNeutralTeamId(){return neutralTeamId;}
		bool IsOtherHostile(Actor* actor) const;
		uint8 GetTeamId() const {return mTeamId;};
		void SetTeamId(uint8 teamId){mTeamId = teamId;};
		virtual void ApplyDamage(float damage);
		sf::Sprite GetSprite() {return mSprite;}
		const sf::Sprite GetSprite() const {return mSprite;}

	private:
		void CentrePivot();
		void InitializePhysics();
		void UninitializePhysics();
		void UpdatePhysicsBodyTransform();

		World* mOwningWorld;
		bool mHasBegunPlay;
		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
		b2Body* mPhysicsBody;
		bool mPhysicsEnabled;
		const static uint8 neutralTeamId = 255;
		uint8 mTeamId;

	};

	
}
