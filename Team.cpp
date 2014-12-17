#include "Team.h"
#include <stdlib.h>

Team::Team()
{
}


Team::~Team()
{
	for (int i = 0; i < Ships.size(); i++)
	{
		delete Ships.at(i);
	}
}


void Team::AddShip(PlayerShip* pShip, int pMapSize)
{
	sf::Color Outline(255, 255, 255, 255);
	sf::Color Trasparency(TeamColor.r, TeamColor.g, TeamColor.b, 128);
	Ships.push_back(pShip);
	Ships.back()->ShipSprite.setFillColor(TeamColor);
	Ships.back()->ShipSprite.setOutlineColor(Outline);
	Ships.back()->ThrustSprite.setFillColor(Trasparency);

	Ships.back()->Respawn(pMapSize);
	Ships.back()->Health = -1;
}

void Team::AddShip(AIShip* pShip, int pMapSize)
{
	sf::Color Outline(255, 255, 255, 255);
	sf::Color Trasparency(TeamColor.r, TeamColor.g, TeamColor.b, 128);
	Ships.push_back(pShip);
	Ships.back()->ShipSprite.setFillColor(TeamColor);
	Ships.back()->ShipSprite.setOutlineColor(Outline);
	Ships.back()->ThrustSprite.setFillColor(Trasparency);

	Ships.back()->Respawn(pMapSize);
	Ships.back()->Health = -1;
}

void Team::AddShip(GenShip* pShip, int pMapSize)
{
	sf::Color Outline(255, 255, 255, 255);
	sf::Color Trasparency(TeamColor.r, TeamColor.g, TeamColor.b, 128);
	Ships.push_back(pShip);
	Ships.back()->ShipSprite.setFillColor(TeamColor);
	Ships.back()->ShipSprite.setOutlineColor(Outline);
	Ships.back()->ThrustSprite.setFillColor(Trasparency);

	Ships.back()->Respawn(pMapSize);
	Ships.back()->Health = -1;
}

void Team::Update(sf::Time pTime, int pMapSize, bool IsPlayerTeam)
{
	for (int i = 0; i < Ships.size(); i++)
	{
		Ships.at(i)->Update(pTime);

		if (IsPlayerTeam && i == 0)
		{
			Ships.at(i)->UpdateProjectiles(pTime, pMapSize, true);
		}
		else
		{
			Ships.at(i)->UpdateProjectiles(pTime, pMapSize, false);
		}
	}
}

void Team::Render(sf::RenderWindow* pTarget, bool IsUpPressed)
{
	for (int i = 0; i < Ships.size(); i++)
	{
		for (int j = 0; j < Ships.at(i)->Projectiles.size(); j++)
		{
			Ships.at(i)->Projectiles.at(j)->Render(pTarget);
		}
		if (Ships.at(i)->IsThrusting && IsUpPressed && i == 0)
			pTarget->draw(Ships.at(i)->ThrustSprite);
		pTarget->draw(Ships.at(i)->ShipSprite);

		sf::RectangleShape Healthbar;

		if (Ships.at(i)->Health > 80)
			Healthbar.setFillColor(sf::Color::Green);
		else
			if (Ships.at(i)->Health > 60)
				Healthbar.setFillColor(sf::Color(128, 255, 0));
			else
				if (Ships.at(i)->Health > 40)
					Healthbar.setFillColor(sf::Color::Yellow);
				else
					if (Ships.at(i)->Health > 20)
						Healthbar.setFillColor(sf::Color(255, 128, 0));
					else
						Healthbar.setFillColor(sf::Color::Red);

		Healthbar.setSize(sf::Vector2f(Ships.at(i)->Health / 2, 5));

		Healthbar.setPosition(sf::Vector2f(Ships.at(i)->ShipSprite.getPosition().x - (Healthbar.getSize().x / 2), Ships.at(i)->ShipSprite.getPosition().y + 30));

		pTarget->draw(Healthbar);
	}
}