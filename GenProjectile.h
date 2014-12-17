#pragma once

#include "SfmlHeader.h"

class GenProjectile
{
public:
	GenProjectile();
	~GenProjectile();
	void Update(sf::Time);
	void CalculateVelocity();
	sf::Vector2f Velocity;
	sf::Vector2f Position;
	float Direction;
	float Speed;
};

