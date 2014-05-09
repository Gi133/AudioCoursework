/*
File:	GameController.h
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Uses:	memory, time.h, string, sstream, iostream,
IState.hpp, XACore.hpp, World.h, Player.h, Monster.h.

Description:
Class that controls the game flow. This class holds the instances of all the game objects in the world (and the instance of the world itself)
and is responsible for also setting up the Monster's position in the world.
On every frame, the function ProcessFrame is called which in turn calls the same function on the game objects.
*/

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

	const float MAX_MONSTER_SPAWN_RANGE, MIN_MONSTER_SPAWN_RANGE;
	const float MAX_MUSIC_BOX_SPAWN_RANGE, MIN_MUSIC_BOX_SPAWN_RANGE;
	const float MAX_MUSIC_BOX_START_DELAY, MIN_MUSIC_BOX_START_DELAY;

	D3DXVECTOR2 monsterPosition;
	unique_ptr<World> world;
	unique_ptr<Player> player;
	unique_ptr<Monster> monster;
};
//	END CLASS
