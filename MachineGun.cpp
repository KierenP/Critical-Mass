#include "MachineGun.h"


MachineGun::MachineGun(sf::Vector2f pPosition, float pRotation, sf::Vector2f pVelocity)
{
	Damage = 20;
	Cooldown = 0.1;
	Speed = 500;


	Velocity = pVelocity;
	Position = pPosition;

	Direction = pRotation;
	Sprite.setRotation(pRotation);

	CalculateVelocity();
	
	Sprite.setFillColor(sf::Color::White);
	Sprite.setSize(sf::Vector2f(2, 10));
	Sprite.setOrigin(Sprite.getSize().x / 2, Sprite.getSize().y / 2);
}


MachineGun::~MachineGun()
{
}

void MachineGun::Render(sf::RenderWindow* pTarget)
{
	Sprite.setPosition(SpritePos);
	pTarget->draw(Sprite);
}
