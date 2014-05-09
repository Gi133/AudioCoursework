/*
File:	GameObject.cpp
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Description:
Look at GameObject.h for details on this class.

Notes and Possible Optimizations:
Turn functions are almost identical, by casting the enum into an int with some checks maybe the switch statement can be eliminated
and instead pass in +1 or -1 as turn parameters which would then be added to the current heading's int value.
*/

#include "GameObject.h"

GameObject::GameObject()
{
	position.x = position.y = 0;

	walkingSound = nullptr;
	breathingSound = nullptr;
	deathSound = nullptr;

	heading = North;
	walkingSpeed = 1.0f;
	alive = true;

	// Setup the heading vectors
	// North
	headingVectors[0].x = 0.0f;
	headingVectors[0].y = 0.0f;
	headingVectors[0].z = 1.0f;

	// South
	headingVectors[1].x = 0.0f;
	headingVectors[1].y = 0.0f;
	headingVectors[1].z = -1.0f;

	// East
	headingVectors[2].x = 1.0f;
	headingVectors[2].y = 0.0f;
	headingVectors[2].z = 0.0f;

	// West
	headingVectors[3].x = -1.0f;
	headingVectors[3].y = 0.0f;
	headingVectors[3].z = 0.0f;
} // End of Constructor.

GameObject::~GameObject()
{
	if (walkingSound->IsValid())
		walkingSound->Stop();

	if (breathingSound->IsValid())
		breathingSound->Stop();

	if (deathSound->IsValid())
		deathSound->Stop();
} // End of Destructor

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
} // End of Turn Left function

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
} // End of Turn Right function.

bool GameObject::TimerCheck(float& timer, const float dt, const float time)
{
	timer += dt;

	if (timer >= time)
	{
		timer = 0;
		return true;
	}
	else
		return false;
} // End of CheckTimer function.