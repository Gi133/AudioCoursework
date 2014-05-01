#include "GameObject.h"

GameObject::GameObject()
{
	position.x = position.y = 0;
	walkingSound = nullptr;
	breathingSound = nullptr;
	deathSound = nullptr;
	heading = North;
	walkingSpeed = 1.0f;
}

GameObject::~GameObject()
{
	if (walkingSound->IsValid())
		walkingSound->Stop();
		
	if (breathingSound->IsValid())
		breathingSound->Stop();
	
	if (deathSound->IsValid())
		deathSound->Stop();
}

void GameObject::Stop()
{
	walkingSound->Stop();
	breathingSound->Stop();
	deathSound->Stop();
} // End of Stop Function

void GameObject::MoveForward()
{
	switch (heading)
	{
	case East:
		position.x += walkingSpeed;
		break;

	case North:
		position.y += walkingSpeed;
		break;

	case South:
		position.y -= walkingSpeed;
		break;

	case West:
		position.x -= walkingSpeed;
		break;
	}

	// Play walking sound.
	walkingSound->Play();
} // End of Walk Forward function.

void GameObject::TurnLeft()
{
	switch (heading)
	{
	case East:
		heading = North;
		break;

	case North:
		heading = West;
		break;

	case South:
		heading = East;
		break;

	case West:
		heading = South;
		break;
	}

	// Play walking sound.
	walkingSound->Play();
}

void GameObject::TurnRight()
{
	switch (heading)
	{
	case East:
		heading = South;
		break;

	case North:
		heading = East;
		break;

	case South:
		heading = West;
		break;

	case West:
		heading = North;
		break;
	}

	// Play walking sound.
	walkingSound->Play();
}

void GameObject::LoadBreathingAudio(std::string filePath)
{
	breathingSound.reset(new XASound(filePath));
}