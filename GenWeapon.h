#pragma once
#include "GenProjectile.h"
class GenWeapon :
	public GenProjectile
{
public:
	GenWeapon();
	~GenWeapon();
	float Damage;
	float Cooldown;
	virtual void Render(sf::RenderWindow*);
	void SetVelocity(sf::Vector2f);
	sf::Vector2f SpritePos;
};

