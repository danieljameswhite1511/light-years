#pragma once
#include "PlayerSpaceship/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"

namespace ly {
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& texturePath)
		:Spaceship(owningWorld, texturePath)
	, mMoveInput{}
	, mSpeed(200.f)
	{
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	
	void PlayerSpaceship::HandleInput()
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mMoveInput.y = -1.f;

		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mMoveInput.y = 1.f;

		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mMoveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mMoveInput.x = 1.f;
		}
		ClampInputOnEdge();
		NormalizeInput();
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(mMoveInput);
		LOG("move input is now: %f, %f", mMoveInput.x, mMoveInput.y);
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
	}

	void PlayerSpaceship::ClampInputOnEdge()
	{
		
		if(GetActorPosition().x < 0 && mMoveInput.x == -1.f)
		{
			mMoveInput.x = 0.f;
		}

		if(GetActorPosition().x > GetWindowSize().x && mMoveInput.x == 1.f)
		{
			mMoveInput.x = 0.f;
		}

		if (GetActorPosition().y < 0 && mMoveInput.y == -1.f)
		{
			mMoveInput.y = 0.f;
		}

		if (GetActorPosition().y > GetWindowSize().y && mMoveInput.y == 1.f)
		{
			mMoveInput.y = 0.f;
		}

	}
}
