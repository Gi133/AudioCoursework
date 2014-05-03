#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	void Start(); // Override GameObject Start function.
	void ProcessTurn(const float dt, const D3DXVECTOR2 playerPosition, const X3DAUDIO_LISTENER* playerListener); // Override GameObject ProcessTurn function

	X3DAUDIO_EMITTER GetAudioEmitter();

	Monster(int positionX, int positionY);
	virtual ~Monster();

private:
	void ProcessMovement(const D3DXVECTOR2 playerPosition); // Function that figures out where the monster should move to next.
	void UpdateEmitterPosition();
	void CheckIfAlive(const float dt); // Function to check if monster is still alive, based on timer. If it dies this function will also play the death sound.

	// Functions to apply 3D effects.
	void ApplySoundEffects(const X3DAUDIO_LISTENER* listener);
	void Walking3DEffect(const X3DAUDIO_LISTENER* listener);
	void Breathing3DEffect(const X3DAUDIO_LISTENER* listener);
	void Death3DEffect(const X3DAUDIO_LISTENER* listener);

	const float MOVEMENT_TIME_DELAY; // Time delay between monster movements, in seconds.
	float movementTimer;

	const float MONSTER_LIFE_TIME; // Value representing the time the monster has to live.
	float lifeTimer;

	float distanceX, distanceY; // Distance between monster and target.
	float moveSpeed; // Move speed for the monster.
	X3DAUDIO_EMITTER audioEmitter;
	XAUDIO2_VOICE_DETAILS details;
};
