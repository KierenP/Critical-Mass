#pragma once
#include "PlayerShip.h"
#include "AIShip.h"

class Team
{
public:
	Team();
	~Team();
	sf::Color TeamColor;
	vector<GenShip*> Ships;
	void AddShip(GenShip*, int);
	void AddShip(PlayerShip*, int);
	void AddShip(AIShip*, int);
	void Update(sf::Time, int, bool);
	void Render(sf::RenderWindow*, bool);
};

