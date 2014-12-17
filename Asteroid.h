#pragma once
#include "SfmlHeader.h"

class Asteroid
{
public:
	Asteroid();
	~Asteroid();
	bool ConvexCheck(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
	bool Generate(sf::Vector2f pPosition);
	sf::ConvexShape Sprite;
	sf::Vector2f Position;
};

