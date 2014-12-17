#pragma once
#include "GenShip.h"
class PlayerShip :
	public GenShip
{
public:
	PlayerShip();
	~PlayerShip();
	void MoveDecide(sf::Time);
};

