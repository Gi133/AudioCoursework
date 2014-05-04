/*
File:	World.h
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Uses: Windows.h, X3DAudio, memory, XASound.hpp

Description:
World class, contains functionality for the ambient audio in the world.

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
using AllanMilne::Audio::XASound;

class World
{
public:
	World();
	~World();

	void Start(); // Start ambient audio.
	void Stop(); // Stop ambient audio.
	void LoadAmbientSound(std::string filePath){ ambientAudio.reset(new XASound(filePath)); }

private:
	unique_ptr<XASound> ambientAudio; // Ambient audio/music for the world.
};
