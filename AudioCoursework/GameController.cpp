#include "GameController.h"

// Windows includes
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
using std::endl;

// Framework includes
#include "XACore.hpp"
using AllanMilne::Audio::XACore;

bool GameController::Initialize(HWND aWindow)
{
	if (XACore::GetStatus() != XACore::OK) // Check if something went horribly wrong with XACore.
		return false;

	// Initialize the game objects.

	// Initialize any other variables that may be required.

// 	mRoom.reset(new Room());
// 	if (!mRoom->IsValid())
// 	{
// 		MessageBox(NULL, "Error creating the room.", TEXT("Initialize() - FAILED"), MB_OK | MB_ICONERROR);
// 		return false;
// 	}

	return true;
} // End of Initialize function

bool GameController::Setup()
{
	DisplayInstructions();
	//mRoom->Reset();
	return true;
} // End of Setup function

bool GameController::ProcessFrame(const float deltaTime)
{

	// Player Turn.

	// Monster Turn.


	return true;
} // End of ProcessFrame function

void GameController::Cleanup()
{
	//mRoom->Stop();
}

void GameController::DisplayInstructions()
{
	std::stringstream msg;
	msg << endl << "You must evade the monster using the following controls: " << endl << endl;
	msg << " up arrow \t = move forward 1 step in the current direction. " << endl;
	msg << " left/right arrows \t = turn 90 degrees counter-clockwise / clockwise respectively. " << endl;
	msg << " 'R' \t = reset player back to start position in the room. " << endl;
	msg << " 'I' \t = display these instructions. " << endl;
	msg << " escape \t = end the application. " << endl << endl;
	const std::string msgStr = msg.str();
	MessageBox(NULL, msgStr.c_str(), TEXT("Room Escape"), MB_OK | MB_ICONINFORMATION);
}

void GameController::ProcessControls()
{

} // End of ProcessControls function

GameController::GameController()
{
	// Initialize points to "nullpointer and whatnot.
} // End of Constructor function

GameController::~GameController()
{
	// Call Stop function on all relevant game objects and deallocate anything that requires deallocation.
}