/*
File:	GameController.cpp
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Description:
Look at GameController.h for further info.
*/

#include "GameController.h"

GameController::GameController() : MAX_MONSTER_SPAWN_RANGE(20.0f), MIN_MONSTER_SPAWN_RANGE(10.0f), MAX_MUSIC_BOX_SPAWN_RANGE(5.0f), MIN_MUSIC_BOX_SPAWN_RANGE(1.0f),
MAX_MUSIC_BOX_START_DELAY(0.0f), MIN_MUSIC_BOX_START_DELAY(2.0f)
{
	// Initialize points to "nullpointer and whatnot.
	world = nullptr;
	player = nullptr;
	monster = nullptr;

	srand(static_cast<unsigned int>(time(NULL)));
} // End of Constructor function

GameController::~GameController()
{
	// Call Stop function on all relevant game objects and deallocate anything that requires deallocation.
	world->Stop();
	player->Stop();
	monster->Stop();
} // End of Destructor function

bool GameController::Initialize(HWND aWindow)
{
	if (XACore::GetStatus() != XACore::OK) // Check if something went horribly wrong with XACore.
		return false;

	// Figure out the starting position for the monster.
	// NOTE: THE FUNCTION WAS DESIGNED TO BE USED WITH FLOATS FOR ANOTHER COURSEWORK PROJECT SO CAST THE RETURN AS AN INT.
	int monsterPositionX = static_cast<int>(RandomInRange(MIN_MONSTER_SPAWN_RANGE, MAX_MONSTER_SPAWN_RANGE));
	int monsterPositionY = static_cast<int>(RandomInRange(MIN_MONSTER_SPAWN_RANGE, MAX_MONSTER_SPAWN_RANGE));

	// The variables above need to be randomized more so that the monster doesn't start in front and to the right of the player all the time.
	RandomSign(monsterPositionX);
	RandomSign(monsterPositionY);

	// Figure out the position of the music box, as with above.
	int musicBoxPositionX = static_cast<int>(RandomInRange(MIN_MUSIC_BOX_SPAWN_RANGE, MAX_MUSIC_BOX_SPAWN_RANGE));
	int musicBoxPositionY = static_cast<int>(RandomInRange(MIN_MUSIC_BOX_SPAWN_RANGE, MAX_MUSIC_BOX_SPAWN_RANGE));

	// The variables above need to be randomized more so that the music box doesn't always appear to the front and right of the player.
	RandomSign(musicBoxPositionX);
	RandomSign(musicBoxPositionY);

	// Figure out the delay timer for the music box to start playing.
	float musicBoxStartDelay = RandomInRange(MAX_MUSIC_BOX_START_DELAY, MIN_MUSIC_BOX_START_DELAY);

	// Initialize the game objects.
	world.reset(new World(musicBoxPositionX, musicBoxPositionY, musicBoxStartDelay));
	player.reset(new Player);
	monster.reset(new Monster(monsterPositionX, monsterPositionY));

	// Load Ambient Audio
	world->LoadAmbientSound("Audio/AmbientAudio.wav");
	world->LoadMusicBoxSound("Audio/MusicBox.wav");

	// Load Player Audio
	player->LoadBreathingAudio("Audio/PlayerBreathing.wav");
	player->LoadWalkingAudio("Audio/PlayerWalking.wav");
	player->LoadDeathAudio("Audio/PlayerDeath.wav");

	// Load Monster Audio
	monster->LoadBreathingAudio("Audio/MonsterBreathing.wav");
	monster->LoadWalkingAudio("Audio/MonsterWalking.wav");
	monster->LoadDeathAudio("Audio/MonsterDeath.wav");

	return true;
} // End of Initialize function

bool GameController::Setup()
{
	DisplayInstructions();
	world->Start();
	player->Start();
	monster->Start();

	return true;
} // End of Setup function

bool GameController::ProcessFrame(const float deltaTime)
{
	if (GetAsyncKeyState('I') & 0x0001)
		DisplayInstructions();

	// If monster is still alive then go on with the game.
	if (monster->GetAlive() && player->GetAlive())
	{
		world->ProcessTurn(deltaTime, player->GetAudioListener());

		// Player Turn.
		player->ProcessTurn(deltaTime, monster->GetPosition());

		// Monster Turn.
		monster->ProcessTurn(deltaTime, player->GetPosition(), player->GetAudioListener());
	}
	else
	{
		// Game has finished, go into fail state.
	}

	return true;
} // End of ProcessFrame function

void GameController::Cleanup()
{
	world->Stop();
	player->Stop();
} // End of Cleanup function.

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
} // End of Display Instructions function.

float GameController::RandomInRange(const float min, const float max)
{
	float randomNumber = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random number between 0 - 1.
	return ((randomNumber * (max - min)) + min); // Return number between min and max.
} // End of RandomInRange function.

void GameController::RandomSign(int& number)
{
	int randNumber = (rand() % 100) + 1; // 1 to 100

	if (randNumber >= 50)
		number *= 1;
	else
		number *= -1;
} // End of RandomSign function.