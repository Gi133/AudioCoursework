#include "Monster.h"


Monster::Monster(int positionX, int positionY)
{
	position.x = static_cast<float>(positionX);
	position.y = static_cast<float>(positionY);
}


Monster::~Monster()
{
}

void Monster::Start()
{

}

void Monster::ProcessTurn(const float dt, const D3DXVECTOR2 playerPosition, const HeadingDirection playerHeading)
{
	ProcessMovement(playerPosition);
}

void Monster::ProcessMovement(const D3DXVECTOR2 playerPosition)
{
	// Calculate the distance X and Y between monster and its target.
	distanceX = playerPosition.x - position.x;
	distanceY = playerPosition.y - position.y;

	// Check/Adjust Heading and move.
	if (abs(distanceX) < abs(distanceY)) // Easier to close in on the x axis
	{
		// Check heading
		if (distanceX > 0) // if distance X is positive
		{
			// Adjust heading to East
			SetHeading(East);
			position.x++;
		}
		else
		{
			// Adjust heading to West
			SetHeading(West);
			position.x--;
		}
	}
	else
	{
		// Check heading
		if (distanceY > 0)
		{
			// Adjust heading to North
			SetHeading(North);
			position.y++;
		}
		else
		{
			// Adjust heading to South
			SetHeading(South);
			position.y--;
		}
	}
}