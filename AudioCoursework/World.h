/*
File:	World.h
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Uses: Windows.h, X3DAudio, memory, XASound.hpp

Description:
World class, contains functionality for the ambient audio in the world.
While sharing many of the game object functionality, it does not inherit from it.

Notes:
This class could be expanded to hold other world/level data.
*/

#pragma once

// Includes.
#include <Windows.h>
#include <X3DAudio.h>
#include <memory>
using std::unique_ptr;

#include "XASound.hpp"
#include "XACore.hpp"
using AllanMilne::Audio::XACore;
using AllanMilne::Audio::XASound;

class World
{
public:
	World(const int MUSIC_BOX_POSITION_X, const int MUSIC_BOX_POSITION_Y, const float MUSIC_BOX_START_DELAY);
	~World();

	void Start(); // Start ambient audio.
	void Stop(); // Stop ambient audio.
	void ProcessTurn(const float dt, const X3DAUDIO_LISTENER* playerListener);

	void LoadAmbientSound(std::string filePath){ ambientAudio.reset(new XASound(filePath)); }
	void LoadMusicBoxSound(std::string filePath){ musicBoxAudio.reset(new XASound(filePath)); }

	X3DAUDIO_EMITTER* GetAudioEmitter(){ return &audioEmitter; }

private:
	bool TimerCheck(float& timer, const float dt, const float time);
	void ApplySoundEffects(const X3DAUDIO_LISTENER* playerListener);

	unique_ptr<XASound> ambientAudio, musicBoxAudio; // Ambient audio/music for the world and music box.
	XAUDIO2_VOICE_DETAILS details;
	X3DAUDIO_EMITTER audioEmitter;

	// Music box timer variables.
	float musicBoxDelay, musicBoxTimer;
};
