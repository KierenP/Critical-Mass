#pragma once
#include "GenWeapon.h"


class MachineGun :
	public GenWeapon
{
public:
	MachineGun(sf::Vector2f, float, sf::Vector2f);
	~MachineGun();
	sf::RectangleShape Sprite;
	void Render(sf::RenderWindow*);
};

