#pragma once

// Includes.
#include <memory>
using std::unique_ptr;

#include "IState.hpp"
using AllanMilne::IState;

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
	void ProcessControls();
};
//	END CLASS
