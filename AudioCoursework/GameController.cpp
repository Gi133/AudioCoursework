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

GameController::GameController()
{
	// Initialize points to "nullpointer and whatnot.
	world = nullptr;
	player = nullptr;

	turnCounter = 0;
} // End of Constructor function

GameController::~GameController()
{
	// Call Stop function on all relevant game objects and deallocate anything that requires deallocation.
	world->Stop();
	player->Stop();
} // End of Destructor function

bool GameController::Initialize(HWND aWindow)
{
	if (XACore::GetStatus() != XACore::OK) // Check if something went horribly wrong with XACore.
		return false;

	// Initialize the game objects.
	world.reset(new World);
	player.reset(new Player);

	// Initialize any other variables that may be required.
	world->LoadAmbientSound("Audio/AmbientAudio.wav");

	player->LoadBreathingAudio("Audio/PlayerBreathing.wav");
	player->LoadWalkingAudio("Audio/PlayerWalking.wav");
	player->LoadDeathAudio("Audio/PlayerDeath.wav");

	return true;
} // End of Initialize function

bool GameController::Setup()
{
	DisplayInstructions();
	world->Start();
	player->Start();

	return true;
} // End of Setup function

bool GameController::ProcessFrame(const float deltaTime)
{
	if (GetAsyncKeyState('I') & 0x0001) 
		DisplayInstructions();

	// Player Turn.
	player->ProcessTurn(deltaTime);

	// Monster Turn.

	turnCounter++;
	return true;
} // End of ProcessFrame function

void GameController::Cleanup()
{
	world->Stop();
	player->Stop();
}

void GameController::DisplayInstructions()
{
	std::stringstream msg;
	msg << endl << "You must evade the monster using the following controls: " << endl << endl;
	msg << " Up Arrow:	Move forward 1 step in the current direction." << endl;
	msg << " Left/Right Arrow:	Turn Left and Right. " << endl;
	msg << " 'I':		Display this instruction box again. " << endl;
	msg << " ESC:		Exit the Application. " << endl << endl;
	const std::string msgStr = msg.str();
	MessageBox(NULL, msgStr.c_str(), TEXT("Monster Evade"), MB_OK | MB_ICONINFORMATION);
}