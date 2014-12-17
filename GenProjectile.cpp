#include "GenProjectile.h"


GenProjectile::GenProjectile()
{
}


GenProjectile::~GenProjectile()
{
}


void GenProjectile::Update(sf::Time pTime)
{
	Position.x += Velocity.x * pTime.asSeconds();
	Position.y += Velocity.y * pTime.asSeconds();
}


void GenProjectile::CalculateVelocity()
{
	Velocity.x += cos((Direction - 90) * 3.1415926535 / 180.0) * Speed;
	Velocity.y += sin((Direction - 90) * 3.1415926535 / 180.0) * Speed;
}
