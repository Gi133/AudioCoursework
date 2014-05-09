/*
File:	Player.h
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Inherits:	GameObject.h

Description:
Player Class that inherits from GameObject. It contains functionality to facilitate movement in the game world as well as some delay values for the player breathing audio.
The breathing becomes more rapid the closer the monster is to the player, for this reason the monster position is passed in every update.
This class also contains a listener object and functionality to update the listener heading and position.
*/

#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	void Start(); // Override GameObject Start function.
	void ProcessTurn(const float dt, const D3DXVECTOR2 monsterPosition); // Override GameObject ProcessTurn function

	X3DAUDIO_LISTENER* GetAudioListener(){ return &audioListener; }

	Player();
	virtual ~Player();

private:
	void Movement(); // Move function, essentially checks controls and moves or turns the player.
	void UpdateListener(); // Function to update the listener position and orientation.
	void UpdateBreathingDelay(const D3DXVECTOR2 monsterPosition);

	// Breathing delay variables.
	float breathingTimer, breathingDelay;
	const float BREATHING_MAX_DELAY, BREATHING_MIN_DELAY, BREATHING_MAX_DISTANCE;
	X3DAUDIO_LISTENER audioListener;
};
