#pragma once
#include "GenWeapon.h"

using namespace::std;

class GenShip :
	public GenProjectile
	
{
public:
	GenShip();
	~GenShip();
	void Accelerate(sf::Time);
	void Fire1();
	void Fire2();
	void UpdateProjectiles(sf::Time, int, bool);
	void TurnLeft(sf::Time);
	void TurnRight(sf::Time);
	void Damage(float);
	void Respawn(int);
	virtual void MoveDecide(sf::Time, int);
	sf::Clock TimeClock1;
	sf::Clock TimeClock2;
	sf::Clock invincibility;
	bool IsThrusting;
	int Weapon1;
	int Weapon2;
	vector<GenWeapon*> Projectiles;
	float Thrust;
	float TurnSpeed;
	sf::Time PrevTime;
	sf::CircleShape ShipSprite;
	sf::CircleShape ThrustSprite;
	float Health;
	string PilotName;
};

