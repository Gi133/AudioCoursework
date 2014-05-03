#pragma once

// Includes.
#include <memory>
#include <time.h>
#include <string>
#include <sstream>
#include <iostream>
using std::unique_ptr;
using std::endl;

#include "IState.hpp"
#include "XACore.hpp"
using AllanMilne::IState;
using AllanMilne::Audio::XACore;

#include "World.h"
#include "Player.h"
#include "Monster.h"

//	BEGIN CLASS
class GameController :public IState
{
public:
	//IState interface stuff.
	bool Initialize(HWND aWindow);
	bool Setup(); // Setup everything, display the instructions.
	bool ProcessFrame(const float deltaTime);
	void Cleanup();

	// Constructor and Destructor
	GameController();
	virtual ~GameController();

private:
	void DisplayInstructions();
	float RandomInRange(const float min, const float max); // Function to generate a number between a minimum and a maximum value provided.
	void RandomSign(int& number); // Function to randomize the sign of a number (positive or negative).
	D3DXVECTOR2 monsterPosition;

	const float MAX_MONSTER_SPAWN_RANGE, MIN_MONSTER_SPAWN_RANGE;

	unique_ptr<World> world;
	unique_ptr<Player> player;
	unique_ptr<Monster> monster;
};
//	END CLASS
