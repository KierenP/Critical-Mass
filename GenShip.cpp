#include "GenShip.h"
#include "MachineGun.h"
#include <cmath>



GenShip::GenShip()
{
	ShipSprite.setRadius(25);
	ShipSprite.setPointCount(3);

	ThrustSprite.setRadius(20);
	ThrustSprite.setPointCount(3);
	ThrustSprite.setOrigin(ThrustSprite.getPoint(3));

	ShipSprite.setPosition(sf::Vector2f(450, 450));
	ShipSprite.setOrigin(25, 25);
	ShipSprite.setFillColor(sf::Color(64, 64, 64, 255));
	ShipSprite.setOutlineColor(sf::Color(255, 255, 255, 255));
	ShipSprite.setOutlineThickness(1);

	Direction = 30;
	Health = 100000;
	PilotName = "No Name Given";
	Thrust = 500;
	TurnSpeed = 250;
}

void GenShip::MoveDecide(sf::Time pTime, int Move)
{

}

GenShip::~GenShip()
{
}


void GenShip::Accelerate(sf::Time pTime)
{
	if (invincibility.getElapsedTime().asSeconds() > 1)
	{
		IsThrusting = true;
		Velocity.x += cos((Direction - 90) * 3.1415926535 / 180.0) * Thrust * pTime.asSeconds();
		Velocity.y += sin((Direction - 90) * 3.1415926535 / 180.0) * Thrust * pTime.asSeconds();
	}
	else
	{
		IsThrusting = false;
	}
}


void GenShip::Fire1()
{
	if (Weapon1 == 0)	//MachineGun
	{
		if (TimeClock1.getElapsedTime().asSeconds() > 0.2)
		{
			TimeClock1.restart();
			Projectiles.push_back(new MachineGun(Position, (Direction + (rand() % 11 - 5)), Velocity));
			//Projectiles.push_back(new MachineGun(Position, Direction, Velocity));
			Projectiles.back()->CalculateVelocity();

			/*TimeClock1.restart();
			Projectiles.push_back(Weapon1);
			Projectiles.back()->Direction = Direction;
			Projectiles.back()->SetVelocity(Velocity);
			Projectiles.back()->CalculateVelocity();*/

			/*GenWeapon Temp1;
			Temp1 = *Weapon1;
			Temp1.Direction = Direction;
			Temp1.SetVelocity(Velocity);
			Temp1.CalculateVelocity();

			if (MachineGun *p = dynamic_cast<MachineGun*>(Weapon1))
			{
			Projectiles.push_back(new MachineGun());
			}*/
		}
	}
}


void GenShip::Fire2()
{
	if (Weapon2 == 0)	//MachineGun
	{
		if (TimeClock2.getElapsedTime().asSeconds() > 1)
		{
			TimeClock2.restart();
			//Projectiles.push_back(new MachineGun(Position, (Direction + (rand() % 11 - 5)), Velocity));
			Projectiles.push_back(new MachineGun(Position, Direction, Velocity));
			Projectiles.back()->CalculateVelocity();

			/*TimeClock1.restart();
			Projectiles.push_back(Weapon1);
			Projectiles.back()->Direction = Direction;
			Projectiles.back()->SetVelocity(Velocity);
			Projectiles.back()->CalculateVelocity();*/

			/*GenWeapon Temp1;
			Temp1 = *Weapon1;
			Temp1.Direction = Direction;
			Temp1.SetVelocity(Velocity);
			Temp1.CalculateVelocity();

			if (MachineGun *p = dynamic_cast<MachineGun*>(Weapon1))
			{
			Projectiles.push_back(new MachineGun());
			}*/
		}
	}
}


void GenShip::UpdateProjectiles(sf::Time pTime, int pMapSize, bool IsPlayerShip)
{
	if (IsPlayerShip)
	{
		ShipSprite.setPosition(Position.x / pMapSize, Position.y / pMapSize);
	}

	ThrustSprite.setPosition(ShipSprite.getPosition());

	ShipSprite.setRotation(Direction);
	ThrustSprite.setRotation(Direction);

	for (unsigned int i = 0; i < Projectiles.size(); i++)
	{
		Projectiles.at(i)->Update(pTime);
	}
}

void GenShip::TurnLeft(sf::Time pTime)
{
	Direction -= TurnSpeed * pTime.asSeconds();

	if (Direction > 360)
	{
		Direction -= 360;
	}
}

void GenShip::TurnRight(sf::Time pTime)
{
	Direction += TurnSpeed * pTime.asSeconds();

	if (Direction < 0)
	{
		Direction += 360;
	}
}

void GenShip::Damage(float pDamage)
{
	Health -= pDamage;
}

void GenShip::Respawn(int pMapSize)
{
	Position = sf::Vector2f(rand() % (1900 * (pMapSize)), rand() % (1000 * (pMapSize)));		   
}