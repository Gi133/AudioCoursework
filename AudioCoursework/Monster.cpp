/*
File:	Monster.cpp
Version:	1.1
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Description:
Look at Monster.h for details on this class.
*/

#include "Monster.h"

Monster::Monster(int positionX, int positionY) : MOVEMENT_TIME_DELAY(5.0f), MONSTER_LIFE_TIME(200.0f)
{
	position.x = static_cast<float>(positionX);
	position.y = static_cast<float>(positionY);

	walkingSpeed = 1;
	movementTimer = 0.0f;
	lifeTimer = 0.0f;

	// Update emitter position.
	UpdateEmitterPosition();
	audioEmitter.Position.y = 0;

	// Zero the audio emitter.
	SecureZeroMemory(&audioEmitter, sizeof(X3DAUDIO_EMITTER));
} // End of Constructor

Monster::~Monster()
{
	if (walkingSound->IsValid())
		walkingSound->Stop();

	if (breathingSound->IsValid())
		breathingSound->Stop();

	if (deathSound->IsValid())
		deathSound->Stop();
} // End of destructor

void Monster::Start()
{
	// Adjust audio settings.
	breathingSound->SetLooped(true);
	breathingSound->AdjustVolume(20.0f);
	breathingSound->Play();

	walkingSound->SetLooped(false);
	walkingSound->AdjustVolume(10.0f);
	deathSound->SetLooped(false);

	// Set audio emitter settings.
	audioEmitter.CurveDistanceScaler = 1.0f;
} // End of Start function

void Monster::ProcessTurn(const float dt, const D3DXVECTOR2 playerPosition, const X3DAUDIO_LISTENER* playerListener)
{
	// Check if the monster is still alive.
	if (CheckIfAlive(dt))
	{
		UpdateEmitterPosition();
		ApplySoundEffects(playerListener);

		// If time to move
		if (TimerCheck(movementTimer, dt, MOVEMENT_TIME_DELAY))
			ProcessMovement(playerPosition);
	}
	else
	{
		// The monster is dead, set alive value to false and play death sound.
		alive = false;
		deathSound->Play();
	}
} // End of ProcessTurn function.

void Monster::ProcessMovement(const D3DXVECTOR2 playerPosition)
{
	// Calculate the distance X and Y between monster and its target.
	distanceX = playerPosition.x - position.x;
	distanceY = playerPosition.y - position.y;

	// Check/Adjust Heading and move.
	if (abs(distanceX) > abs(distanceY)) // Easier to close in on the x axis
	{
		// Check heading
		if (distanceX > 0) // if distance X is positive
		{
			// Adjust heading to East
			SetHeading(East);
			position.x += walkingSpeed;
		}
		else
		{
			// Adjust heading to West
			SetHeading(West);
			position.x -= walkingSpeed;
		}
	}
	else
	{
		// Check heading
		if (distanceY > 0)
		{
			// Adjust heading to North
			SetHeading(North);
			position.y += walkingSpeed;
		}
		else
		{
			// Adjust heading to South
			SetHeading(South);
			position.y -= walkingSpeed;
		}
	}

	walkingSound->Play();
} // End of ProcessMovement function.

void Monster::ApplySoundEffects(const X3DAUDIO_LISTENER* listener)
{
	Breathing3DEffect(listener);
	Walking3DEffect(listener);
	Death3DEffect(listener);
} // End of ApplySoundEffects function.

void Monster::Walking3DEffect(const X3DAUDIO_LISTENER* listener)
{
	// Apply 3D effect to walking sound.
	walkingSound->GetSourceVoice()->GetVoiceDetails(&details);
	audioEmitter.ChannelCount = details.InputChannels;
	XACore::GetInstance()->Apply3D(walkingSound->GetSourceVoice(), &audioEmitter, listener, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_LPF_DIRECT);
} // End of Walking3DEffect function.

void Monster::Breathing3DEffect(const X3DAUDIO_LISTENER* listener)
{
	// Apply 3D effect to breathing sound.
	breathingSound->GetSourceVoice()->GetVoiceDetails(&details);
	audioEmitter.ChannelCount = details.InputChannels;
	XACore::GetInstance()->Apply3D(breathingSound->GetSourceVoice(), &audioEmitter, listener, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_LPF_DIRECT);
} // End of Breathing3DEffect function.

void Monster::Death3DEffect(const X3DAUDIO_LISTENER* listener)
{
	// Apply 3D effect to death sound.
	deathSound->GetSourceVoice()->GetVoiceDetails(&details);
	audioEmitter.ChannelCount = details.InputChannels;
	XACore::GetInstance()->Apply3D(deathSound->GetSourceVoice(), &audioEmitter, listener, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_LPF_DIRECT);
} // End of Death3DEffect function.

void Monster::UpdateEmitterPosition()
{
	audioEmitter.Position.x = position.x;
	audioEmitter.Position.z = position.y;
} // End of UpdateEmitterPosition function.

bool Monster::CheckIfAlive(const float dt)
{
	if (TimerCheck(lifeTimer, dt, MONSTER_LIFE_TIME))
		return false;
	else
		return true;
} // End of CheckIfAlive function.