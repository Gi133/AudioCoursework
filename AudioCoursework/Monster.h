#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	void Start(); // Override GameObject Start function.
	void ProcessTurn(const float dt, const D3DXVECTOR2 playerPosition, const HeadingDirection playerHeading); // Override GameObject ProcessTurn function

	Monster(int positionX, int positionY);
	virtual ~Monster();

private:
	void ProcessMovement(const D3DXVECTOR2 playerPosition); // Function that figures out where the monster should move to next.

	float distanceX, distanceY; // Distance between monster and target.
	float moveSpeed; // Move speed for the monster.
	X3DAUDIO_EMITTER soundEmitter;
};

