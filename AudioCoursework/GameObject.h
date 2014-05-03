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

	// Getters and Setters
	void SetPosition(float x = 0.0f, float y = 0.0f) { position.x = x, position.y = y; } // Used to force the position of the game object.
	void SetHeading(HeadingDirection newHeading){ heading = newHeading; } // Used to force the heading of the game object.
	HeadingDirection GetHeading(){ return heading; }
	D3DXVECTOR2 GetPosition(){ return position; }
	bool GetAlive(){ return alive; }

	// File loading
	void LoadWalkingAudio(std::string filePath){ walkingSound.reset(new XASound(filePath)); }
	void LoadBreathingAudio(std::string filePath);
	void LoadDeathAudio(std::string filePath){ deathSound.reset(new XASound(filePath)); }

	virtual void ProcessTurn(){ return; } // Function called to process the objects turn.

	inline bool IsValid() const { return (walkingSound->IsValid() && breathingSound->IsValid() && deathSound->IsValid()); } // Check that everything was setup properly.
	virtual void Stop(); // Stop playing audio.
	virtual void Start(){ return; } // Start playing audio.

protected:
	// Functions to facilitate movement in the game world.
	void MoveForward();
	void TurnLeft();
	void TurnRight();
	X3DAUDIO_VECTOR ConvertHeadingToVector();

	bool TimerCheck(float& timer, const float dt, const float time); // Function that takes in a timer variable, deltaTime and a time to check against.

	D3DXVECTOR2 position;
	X3DAUDIO_VECTOR headingVectors[4];
	unique_ptr<XASound> walkingSound, breathingSound, deathSound;
	HeadingDirection heading;
	float walkingSpeed;
	bool alive; // If the object is alive/active in the scene.
};
