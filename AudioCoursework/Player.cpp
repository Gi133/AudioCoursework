/*
File:	Player.cpp
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Description:
Look at Player.h for details on this class.
*/

#include "Player.h"

Player::Player() : BREATHING_MAX_DELAY(5.0f), BREATHING_MIN_DELAY(2.0f), BREATHING_MAX_DISTANCE(20.0f)
{
	// Setup the listener.
	SecureZeroMemory(&audioListener, sizeof(X3DAUDIO_LISTENER));

	// Setup listener orientation
	audioListener.OrientFront = ConvertHeadingToVector();
	audioListener.OrientTop.x = 0.0f;
	audioListener.OrientTop.y = 1.0f;
	audioListener.OrientTop.z = 0.0f;

	// Setup listener position, convert from a 2D vector to a 3D vector.
	audioListener.Position.x = position.x;
	audioListener.Position.y = 0.0f;
	audioListener.Position.z = position.y;

	// Setup breathing values.
	breathingTimer = 0.0f;
	breathingDelay = BREATHING_MAX_DELAY;
} // End of Constructor

Player::~Player()
{
	if (walkingSound->IsValid())
		walkingSound->Stop();

	if (breathingSound->IsValid())
		breathingSound->Stop();

	if (deathSound->IsValid())
		deathSound->Stop();
} // End of Destructor

void Player::Start()
{
	breathingSound->SetLooped(false);
	breathingSound->AdjustVolume(-5.0f);
	breathingSound->Play();

	walkingSound->AdjustVolume(-10.0f);

	deathSound->AdjustVolume(10.0f);
} // End of Start function.

void Player::ProcessTurn(const float dt, const D3DXVECTOR2 monsterPosition)
{
	// Check if monster has caught the player.
	if (position != monsterPosition)
	{
		Movement();

		UpdateBreathingDelay(monsterPosition);

		// Check if it's time to take a breath.
		if (TimerCheck(breathingTimer, dt, breathingDelay))
			breathingSound->Play();
	}
	else
	{
		// Monster has caught the player so play death sound and set alive state to false;
		deathSound->Play();
		alive = false;
	}
} // End ProcessTurn function

void Player::Movement()
{
	if (GetAsyncKeyState(VK_UP) & 0x0001)
		MoveForward();

	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
		TurnLeft();

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
		TurnRight();

	UpdateListener();
} // End of Movement function

void Player::UpdateListener()
{
	// Update heading
	audioListener.OrientFront = ConvertHeadingToVector();

	// Update position
	audioListener.Position.x = position.x;
	audioListener.Position.z = position.y;
} // End UpdateListener function.

void Player::UpdateBreathingDelay(const D3DXVECTOR2 monsterPosition)
{
	float distance = sqrt((monsterPosition.x - position.x) + (monsterPosition.y - position.y));

	if (distance < BREATHING_MAX_DISTANCE)
		breathingDelay = BREATHING_MIN_DELAY + (distance / BREATHING_MAX_DISTANCE * BREATHING_MAX_DELAY);
	else
		breathingDelay = BREATHING_MAX_DELAY;
} // End Update Breathing Delay function.