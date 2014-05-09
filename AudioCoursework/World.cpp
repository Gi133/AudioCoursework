/*
File:	World.cpp
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Description:
Look at World.h for details
*/

#include "World.h"

World::World(const int musicBoxPositionX, const int musicBoxPositionY, const float musicBoxStartDelay)
{
	ambientAudio = nullptr;
	musicBoxAudio = nullptr;

	musicBoxTimer = 0.0f;
	musicBoxDelay = musicBoxStartDelay;

	// Zero the audio emitter.
	SecureZeroMemory(&audioEmitter, sizeof(X3DAUDIO_EMITTER));

	// Setup the emitter for the music box audio.
	audioEmitter.Position.x = static_cast<float>(musicBoxPositionX);
	audioEmitter.Position.y = 0.0f;
	audioEmitter.Position.z = static_cast<float>(musicBoxPositionY);
	audioEmitter.CurveDistanceScaler = 1.0f;
} // End of constructor.

World::~World()
{
	if (ambientAudio->IsValid())
		ambientAudio->Stop();
	if (musicBoxAudio->IsValid())
		musicBoxAudio->Stop();
} // End of destructor.

void World::Start()
{
	if (ambientAudio->IsValid())
	{
		ambientAudio->SetLooped(true);
		ambientAudio->AdjustVolume(-10.0f);
		ambientAudio->Play();
	}

	if (musicBoxAudio->IsValid())
	{
		musicBoxAudio->SetLooped(true);
		musicBoxAudio->AdjustVolume(12.0f);
	}
} // End of Start function.

void World::Stop()
{
	if (ambientAudio->IsValid())
		ambientAudio->Stop();
} // End of Stop function.

void World::ProcessTurn(const float dt, const X3DAUDIO_LISTENER* playerListener)
{
	// Check the timer to see if the music box should start playing.
	if ((TimerCheck(musicBoxTimer, dt, musicBoxDelay)) && !musicBoxAudio->IsPlaying())
		musicBoxAudio->Play();

	// Apply positional sound effects.
	ApplySoundEffects(playerListener);
} // End of ProcessTurn function.

void World::ApplySoundEffects(const X3DAUDIO_LISTENER* playerListener)
{
	// Apply 3D effect to music box sound.
	musicBoxAudio->GetSourceVoice()->GetVoiceDetails(&details);
	audioEmitter.ChannelCount = details.InputChannels;
	XACore::GetInstance()->Apply3D(musicBoxAudio->GetSourceVoice(), &audioEmitter, playerListener, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_LPF_DIRECT);
}

bool World::TimerCheck(float& timer, const float dt, const float time)
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