#include "AIShip.h"


AIShip::AIShip()
{
}


AIShip::~AIShip()
{
}


void AIShip::MoveDecide(sf::Time pTime, int Move)
{
	if (Move == 0)
		TurnLeft(pTime);
	if (Move == 1)
		TurnRight(pTime);
	if (Move == 2)
		Fire1();
	if (Move == 3)
		Accelerate(pTime);
}
