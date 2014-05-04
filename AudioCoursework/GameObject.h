/*
File:	GameObject.h
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Uses:	Windows.h, X3DAudio.h, D3DX10math.h, memory, XASound.hpp, XACore.hpp

Description:
Base class to be used for game objects. This class includes functionality to enable game objects to move around in the world
as well as functionality to load audio files for the common sounds that all game objects share. Lastly this base class also includes
functionality to check if the object is alive/active in the world and also a function for timer checking.
*/

#pragma once

// Includes.
#include <Windows.h>
#include <X3DAudio.h>
#include <D3DX10math.h>
#include <memory>
using std::unique_ptr;

#include "XASound.hpp"
#include "XACore.hpp"
using AllanMilne::Audio::XACore;
using AllanMilne::Audio::XASound;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	enum HeadingDirection{ North, South, East, West }; // The heading directions.

	virtual void ProcessTurn(){ return; } // Function called to process the objects turn.

	inline bool IsValid() const { return (walkingSound->IsValid() && breathingSound->IsValid() && deathSound->IsValid()); } // Check that everything was setup properly.
	virtual void Stop(); // Stop playing audio.
	virtual void Start(){ return; } // Start playing audio.

	// File loading
	void LoadWalkingAudio(std::string filePath){ walkingSound.reset(new XASound(filePath)); }
	void LoadBreathingAudio(std::string filePath){ breathingSound.reset(new XASound(filePath)); }
	void LoadDeathAudio(std::string filePath){ deathSound.reset(new XASound(filePath)); }

	// Getters and Setters
	void SetPosition(float x = 0.0f, float y = 0.0f) { position.x = x, position.y = y; } // Used to force the position of the game object.
	void SetHeading(HeadingDirection newHeading){ heading = newHeading; } // Used to force the heading of the game object.

	HeadingDirection GetHeading(){ return heading; }
	D3DXVECTOR2 GetPosition(){ return position; }
	bool GetAlive(){ return alive; }

protected:
	// Functions to facilitate movement in the game world.
	void MoveForward();
	void TurnLeft();
	void TurnRight();

	// Function that converts the object's heading into a vector.
	X3DAUDIO_VECTOR ConvertHeadingToVector(){ return headingVectors[heading]; }
	
	// Function that takes in a timer variable, deltaTime and a time to check against.
	bool TimerCheck(float& timer, const float dt, const float time); 

	D3DXVECTOR2 position;
	X3DAUDIO_VECTOR headingVectors[4];
	unique_ptr<XASound> walkingSound, breathingSound, deathSound;
	HeadingDirection heading;
	float walkingSpeed;
	bool alive; // If the object is alive/active in the scene.
};
