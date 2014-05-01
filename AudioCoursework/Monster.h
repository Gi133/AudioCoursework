#pragma once
#include "GameObject.h"
class Monster :
	public GameObject
{
public:
	void Start(); // Override GameObject Start function.
	void ProcessTurn(const float dt); // Override GameObject ProcessTurn function

	Monster();
	virtual ~Monster();
};

