#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	void Start(); // Override GameObject Start function.
	void ProcessTurn(const float dt, const D3DXVECTOR2 monsterPosition); // Override GameObject ProcessTurn function

	X3DAUDIO_LISTENER* GetAudioListener();

	Player();
	virtual ~Player();

private:
	void Breathe(const float dt); // Breathing function, takes in the deltaTime and checks if it's time for for the player to breathe.
	void Movement(); // Move function, essentially checks controls and moves or turns the player.
	void UpdateListener(); // Function to update the listener position and orientation.
	void UpdateBreathingDelay(const D3DXVECTOR2 monsterPosition);

	// Breathing delay variables.
	float breathingTimer, breathingDelay;
	const float BREATHING_MAX_DELAY, BREATHING_MIN_DELAY, BREATHING_MAX_DISTANCE;
	X3DAUDIO_LISTENER audioListener;
};
