/*
File:	Monster.h
Version:	1.1
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Inherits:	GameObject.h

Description:
Monster class that inherits GameObject base class. Main additions from the base class are functions related to how the monster pathfinds through the world
and also the inclusion of a sound emitter which is used to apply a 3D effect to the sounds.
The monster also has a life timer which is updated every frame and when it reaches 0 the monster dies as well as a movement timer which adds a delay to the monster movements.
Another change is that the ProcessTurn function now takes in the player position as a D3DXVECTOR2 and a pointer to the player listener object along with the deltaTime and the constructor
is called with 2 values that correspond to the starting x and y values for this object.

Change log:
CheckIfAlive function now returns a boolean, this removes a redundant check that appeared in ProcessTurn function.
*/

#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	void Start(); // Override GameObject Start function.
	void ProcessTurn(const float dt, const D3DXVECTOR2 playerPosition, const X3DAUDIO_LISTENER* playerListener); // Override GameObject ProcessTurn function

	X3DAUDIO_EMITTER* GetAudioEmitter(){ return &audioEmitter; }

	Monster(int positionX, int positionY);
	virtual ~Monster();

private:
	void ProcessMovement(const D3DXVECTOR2 playerPosition); // Function that figures out where the monster should move to next.
	void UpdateEmitterPosition(); // Update emitter positions with current position.
	bool CheckIfAlive(const float dt); // Return true if monster is still alive else return false.

	// Functions to apply 3D effects.
	void ApplySoundEffects(const X3DAUDIO_LISTENER* listener); // Function that calls the relevant functions to apply 3D effects to all sounds.
	void Walking3DEffect(const X3DAUDIO_LISTENER* listener); // Function to apply 3D Effect to the walking sound.
	void Breathing3DEffect(const X3DAUDIO_LISTENER* listener); // Function to apply 3D Effect to the breathing sound.
	void Death3DEffect(const X3DAUDIO_LISTENER* listener); // Function to apply 3D Effect to the death sound.

	const float MOVEMENT_TIME_DELAY; // Time delay between monster movements, in seconds.
	float movementTimer;

	const float MONSTER_LIFE_TIME; // Value representing the time the monster has to live.
	float lifeTimer;

	float distanceX, distanceY; // Distance between monster and target.
	float moveSpeed; // Move speed for the monster.
	X3DAUDIO_EMITTER audioEmitter;
	XAUDIO2_VOICE_DETAILS details;
};
