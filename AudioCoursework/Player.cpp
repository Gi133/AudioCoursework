#include "Player.h"


Player::Player() : BREATHING_MAX_DELAY(5.0f), BREATHING_MIN_DELAY(2.0f)
{
	breathingTimer = 0.0f;
	breathingDelay = BREATHING_MAX_DELAY;
}


Player::~Player()
{
}

void Player::Start()
{
	breathingSound->SetLooped(false);
	breathingSound->SetVolume(0.5f);
	breathingSound->Play();
}

void Player::ProcessTurn(const float dt)
{
	Movement();
	Breathe(dt);
}

void Player::Movement()
{
	if (GetAsyncKeyState(VK_UP) & 0x0001) 
		MoveForward();
	
	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
		TurnLeft();
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
		TurnRight();
}

void Player::Breathe(const float dt)
{
	breathingTimer += dt;
	if (breathingTimer >= breathingDelay)
	{
		breathingSound->Play();
		breathingTimer = 0.0f;
	}
}