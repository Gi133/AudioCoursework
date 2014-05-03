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
	void LoadAmbientSound(std::string filePath);

private:
	unique_ptr<XASound> ambientAudio; // Ambient audio/music for the world.
};
