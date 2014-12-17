#pragma once
#include "GenShip.h"

class AIShip :
	public GenShip
{
public:
	AIShip();
	~AIShip();
	void MoveDecide(sf::Time, int); 
};

