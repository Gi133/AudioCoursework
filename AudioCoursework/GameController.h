#pragma once

// Includes.
#include <memory>
using std::unique_ptr;

#include "IState.hpp"
using AllanMilne::IState;

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
	float RandomInRange(const float min, const float max);
	D3DXVECTOR2 monsterPosition

	const float MAX_MONSTER_SPAWN_RANGE, MIN_MONSTER_SPAWN_RANGE;

	unique_ptr<World> world;
	unique_ptr<Player> player;
	unique_ptr<Monster> monster;
	unsigned int turnCounter;
};
//	END CLASS
