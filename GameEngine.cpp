#include "GameEngine.h"

//Most complicated class coming up

GameEngine::GameEngine(sf::RenderWindow* pTarget)
{
	BackgroundSprite.setPosition(sf::Vector2f(0, 0)); 
	BackgroundSprite.setTextureRect(sf::IntRect(0, 0, pTarget->getSize().x + 400, pTarget->getSize().y + 400)); //setting up the stary backround
}


GameEngine::~GameEngine()
{
}

void GameEngine::AddTeam(sf::Color pTeamColor)
{
	Team Temp;
	Temp.TeamColor = pTeamColor;
	Teams.push_back(Temp);     
}

void GameEngine::AiMoveDecide(sf::Time pTime)
{
	for (int i = 0; i < Teams.size(); i++)
	{
		for (int j = 0; j < Teams.at(i).Ships.size(); j++)
		{
			vector<GenShip*> ShipsInLos;

			for (int x = 0; x < Teams.size(); x++)
			{
				for (int y = 0; y < Teams.at(x).Ships.size(); y++)
				{
					bool LosBlocked = false;

					if (i != x)
					{
						for (int k = 0; k < Asteroids.size(); k++)
						{
							if (CheckCross(sf::Vector2f(Teams.at(i).Ships.at(j)->ShipSprite.getPosition()), 
								           sf::Vector2f(Teams.at(x).Ships.at(y)->ShipSprite.getPosition()),
										   sf::Vector2f(Asteroids.at(k).Sprite.getGlobalBounds().left, Asteroids.at(k).Sprite.getGlobalBounds().top),
										   sf::Vector2f(Asteroids.at(k).Sprite.getGlobalBounds().left + Asteroids.at(k).Sprite.getGlobalBounds().width, Asteroids.at(k).Sprite.getGlobalBounds().top)))
							{
								LosBlocked = true;
							}

							if (CheckCross(sf::Vector2f(Teams.at(i).Ships.at(j)->ShipSprite.getPosition()),
								           sf::Vector2f(Teams.at(x).Ships.at(y)->ShipSprite.getPosition()),
										   sf::Vector2f(Asteroids.at(k).Sprite.getGlobalBounds().left + Asteroids.at(k).Sprite.getGlobalBounds().width, Asteroids.at(k).Sprite.getGlobalBounds().top),
										   sf::Vector2f(Asteroids.at(k).Sprite.getGlobalBounds().left + Asteroids.at(k).Sprite.getGlobalBounds().width, Asteroids.at(k).Sprite.getGlobalBounds().top + Asteroids.at(k).Sprite.getGlobalBounds().height)))
							{
								LosBlocked = true;
							}

							if (CheckCross(sf::Vector2f(Teams.at(i).Ships.at(j)->ShipSprite.getPosition()),
								           sf::Vector2f(Teams.at(x).Ships.at(y)->ShipSprite.getPosition()),
										   sf::Vector2f(Asteroids.at(k).Sprite.getGlobalBounds().left + Asteroids.at(k).Sprite.getGlobalBounds().width, Asteroids.at(k).Sprite.getGlobalBounds().top + Asteroids.at(k).Sprite.getGlobalBounds().height),
										   sf::Vector2f(Asteroids.at(k).Sprite.getGlobalBounds().left, Asteroids.at(k).Sprite.getGlobalBounds().top + Asteroids.at(k).Sprite.getGlobalBounds().height)))
							{
								LosBlocked = true;
							}

							if (CheckCross(sf::Vector2f(Teams.at(i).Ships.at(j)->ShipSprite.getPosition()),
								           sf::Vector2f(Teams.at(x).Ships.at(y)->ShipSprite.getPosition()),
										   sf::Vector2f(Asteroids.at(k).Sprite.getGlobalBounds().left, Asteroids.at(k).Sprite.getGlobalBounds().top + Asteroids.at(k).Sprite.getGlobalBounds().height),
										   sf::Vector2f(Asteroids.at(k).Sprite.getGlobalBounds().left, Asteroids.at(k).Sprite.getGlobalBounds().top)))
							{
								LosBlocked = true;
							}
						}

						if (!(LosBlocked))
							ShipsInLos.push_back(Teams.at(x).Ships.at(y));
					}				
				}				
			}

			float DistanceToClosest = 99999999;

			GenShip* Closestship = Teams.at(i).Ships.at(j);

			for (int x = 0; x < ShipsInLos.size(); x++)
			{
				float Distance = (sqrt(pow((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().y - ShipsInLos.at(x)->ShipSprite.getPosition().y), 2) + pow((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().x - ShipsInLos.at(x)->ShipSprite.getPosition().x), 2)));

				if (Distance < DistanceToClosest)
				{
					Closestship = ShipsInLos.at(x);
					DistanceToClosest = Distance;
				}	
			}	

			if ((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().x < 250) && (Teams.at(i).Ships.at(j)->Velocity.x < 0))
			{

			}

			if ((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().x > (1920 - 250)) && (Teams.at(i).Ships.at(j)->Velocity.x > 0))
			{

			}

			if ((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().y < 250) && (Teams.at(i).Ships.at(j)->Velocity.y < 0))
			{

			}

			if ((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().y > (1080- 250)) && (Teams.at(i).Ships.at(j)->Velocity.y > 0))
			{

			}


			vector<GenWeapon*> IncomingBullets;

			for (int k = 0; k < ShipsInLos.size(); k++)
			{
				for (int x = 0; x < ShipsInLos.at(k)->Projectiles.size(); x++)
				{
					int count = 0;
					float CurrentDist = 0;
					float PrevDist = 99999;

					while (true)
					{
						sf::Vector2f ShipPos = Teams.at(i).Ships.at(j)->Position + (sf::Vector2f(count * (Teams.at(i).Ships.at(j)->Velocity.x / 100), count * (Teams.at(i).Ships.at(j)->Velocity.y / 100)));
						sf::Vector2f BulletPos = ShipsInLos.at(k)->Projectiles.at(x)->Position + (sf::Vector2f(count * (ShipsInLos.at(k)->Projectiles.at(x)->Velocity.x / 100), count * (ShipsInLos.at(k)->Projectiles.at(x)->Velocity.y / 100)));

						CurrentDist = sqrt(((ShipPos.x - BulletPos.x) * (ShipPos.x - BulletPos.x)) + ((ShipPos.y - BulletPos.y) * (ShipPos.y - BulletPos.y)));


						if (count == 2)
						{
							int y = 0;
						}


						if (CurrentDist < PrevDist)
						{
							if (CurrentDist < 50)
							{
								IncomingBullets.push_back(ShipsInLos.at(k)->Projectiles.at(x));
							}
							PrevDist = CurrentDist;
							
						}
						else
						{
							break;
						}

						if (count > 1000)
						{
							break;
						}

						count++;
					}
				}
			}

			float CurrentDist = 0;
			float ClosestDist = 99999;
			int ClosestNo = 0;

			for (int k = 0; k < IncomingBullets.size(); k++)
			{
				CurrentDist = sqrt(((Teams.at(i).Ships.at(j)->Position.x - IncomingBullets.at(k)->Velocity.x) * (Teams.at(i).Ships.at(j)->Position.x - IncomingBullets.at(k)->Velocity.x)) + ((Teams.at(i).Ships.at(j)->Position.y - IncomingBullets.at(k)->Velocity.y) * (Teams.at(i).Ships.at(j)->Position.y - IncomingBullets.at(k)->Velocity.y)));

				if (CurrentDist < ClosestDist)
				{
					ClosestDist = CurrentDist;
					ClosestNo = k;
				}

				if (ClosestDist < 150)
				{
					Teams.at(i).Ships.at(j)->MoveDecide(pTime, 3);
				}
			}

			sf::Vector2f PerpendicilarVector = sf::Vector2f(0, 0);

			if (IncomingBullets.size() > 0)
			{
				PerpendicilarVector = sf::Vector2f(IncomingBullets.at(ClosestNo)->Velocity.y, -(IncomingBullets.at(ClosestNo)->Velocity.x));

				float PerpendicularAngle = atan(PerpendicilarVector.y / PerpendicilarVector.x) * 180 / 3.14159;

				if (PerpendicularAngle < 0)
				{
					PerpendicularAngle = 360 + PerpendicularAngle;
				}

				//if (PerpendicularAngle - Teams.at(i).Ships.at(j)->Direction - 90 <= 90 && PerpendicularAngle - Teams.at(i).Ships.at(j)->Direction - 90 >= -90)
				if (PerpendicularAngle - Teams.at(i).Ships.at(j)->Direction + 90 > -90 && PerpendicularAngle - Teams.at(i).Ships.at(j)->Direction + 90 < 90)
				{
					if (PerpendicularAngle - (Teams.at(i).Ships.at(j)->Direction - 90 - 10) < 0)
						Teams.at(i).Ships.at(j)->MoveDecide(pTime, 0);
					else
					{
						if (PerpendicularAngle - (Teams.at(i).Ships.at(j)->Direction - 90 + 10) > 0)
							Teams.at(i).Ships.at(j)->MoveDecide(pTime, 1);
						else
							Teams.at(i).Ships.at(j)->MoveDecide(pTime, 3);
					}
				}
				else
				{
					PerpendicularAngle = PerpendicularAngle + 180;

					if (PerpendicularAngle > 360)
						PerpendicularAngle = PerpendicularAngle - 360;

					if (PerpendicularAngle - (Teams.at(i).Ships.at(j)->Direction - 90 - 10) < 0)
						Teams.at(i).Ships.at(j)->MoveDecide(pTime, 0);
					else
					{
						if (PerpendicularAngle - (Teams.at(i).Ships.at(j)->Direction - 90 + 10) > 0)
							Teams.at(i).Ships.at(j)->MoveDecide(pTime, 1);
						else
							Teams.at(i).Ships.at(j)->MoveDecide(pTime, 3);
					}
				}
			}
			else
			{
				sf::Vector2f totarget = Teams.at(i).Ships.at(j)->Position - Closestship->Position;
				sf::Vector2f VelocityDif = Teams.at(i).Ships.at(j)->Velocity - Closestship->Velocity;

				float a = ((VelocityDif.x) * (VelocityDif.x) + (VelocityDif.y) * (VelocityDif.y)) - (500 * 500);
				float b = ((2 * totarget.x * VelocityDif.x) + (2 * totarget.y * VelocityDif.y));
				float c = ((totarget.x * totarget.x) + (totarget.y * totarget.y));

				float p = -b / (2 * a);
				float q = (float)sqrt((b * b) - 4 * a * c) / (2 * a);

				float t1 = p - q;
				float t2 = p + q;
				float t;

				if (t2 > 0)
				{
					t = t2;
				}
				else
				{
					t = t1;
				}

				sf::Vector2f aimSpot = Closestship->Position + Closestship->Velocity * t;
				sf::Vector2f bulletPath = aimSpot - Teams.at(i).Ships.at(j)->Position;
				float timeToImpact = sqrt(bulletPath.x * bulletPath.x + bulletPath.y * bulletPath.y) / 500;

				sf::Vector2f BulletTargetSpeed = sf::Vector2f((bulletPath.x - Teams.at(i).Ships.at(j)->Velocity.x * t) / t, (bulletPath.y - Teams.at(i).Ships.at(j)->Velocity.y * t) / t);

				//sf::Vector2f aimSpotDif = sf::Vector2f((aimSpot.y - Teams.at(i).Ships.at(j)->Position.y), (aimSpot.x - Teams.at(i).Ships.at(j)->Position.x));

				float Angle = ((atan2f(BulletTargetSpeed.y, BulletTargetSpeed.x)) * 180 / 3.1415926535);
				
				Angle = Angle + 90;
		



				/*if (aimSpotDif.x > 0 && aimSpotDif.y > 0)//Top Right
				{
					Angle = 90 - Angle + 180;
				}

				if (aimSpotDif.x > 0 && aimSpotDif.y < 0)//Bottom Right
				{
					Angle = 360 - (Angle) + 90;
				}

				if (aimSpotDif.x < 0 && aimSpotDif.y < 0)//Bottom Left
				{
					Angle = 360 - (Angle) + 180;
				}

				if (aimSpotDif.x < 0 && aimSpotDif.y > 0)//Top Left
				{
					Angle = 360 - (Angle) + 180;
				}*/
				
				//Angle = 360 - Angle;

				if (ShipsInLos.size() >= 1)
				{
					if ((Angle < (Teams.at(i).Ships.at(j)->Direction + 2)) && (Angle > (Teams.at(i).Ships.at(j)->Direction - 2)))
					{
						Teams.at(i).Ships.at(j)->MoveDecide(pTime, 2);
					}
					else
					{
						if ((int((Angle - (Teams.at(i).Ships.at(j)->Direction))) % 360 > 0) && (int((Angle - (Teams.at(i).Ships.at(j)->Direction))) % 360 < 180))
						{
							Teams.at(i).Ships.at(j)->MoveDecide(pTime, 1);
						}
						else
						{
							Teams.at(i).Ships.at(j)->MoveDecide(pTime, 0);
						}
					}
				}
			}
		}
	}
}

void GameEngine::Update(sf::Time pTime)
{
	for (int i = 0; i < Asteroids.size(); i++)
	{
		Asteroids.at(i).Sprite.setPosition(Asteroids.at(i).Position.x - Teams.at(0).Ships.at(0)->Position.x + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().x,
										   Asteroids.at(i).Position.y - Teams.at(0).Ships.at(0)->Position.y + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().y);  //Calculate the asteriods sprite position on the window relitive to the ship
	}

	AiMoveDecide(pTime);

	for (int i = 0; i < Teams.size(); i++)
	{
		for (int j = 0; j < Teams.at(i).Ships.size(); j++)
		{
			if (Teams.at(i).Ships.at(j)->Health <= 0)
			{
				bool ToutchingAsteroid = false;  //checks to make sure i done spawn into a asteriod ;)

				do 
				{
					ToutchingAsteroid = false;

					Teams.at(i).Ships.at(j)->Respawn(MapSize);
					Teams.at(i).Ships.at(j)->ShipSprite.setPosition(Teams.at(i).Ships.at(j)->Position.x / MapSize, Teams.at(i).Ships.at(j)->Position.y / MapSize);

					for (int k = 0; k < Asteroids.size(); k++)
					{
						if (Asteroids.at(k).Sprite.getGlobalBounds().contains(Teams.at(i).Ships.at(j)->ShipSprite.getPosition()))
						{
							ToutchingAsteroid = true;
						}
					}
				} while (ToutchingAsteroid);

				Teams.at(i).Ships.at(j)->Health = 100;
			}

			if (!(j == 0 && i == 0))
				Teams.at(i).Ships.at(j)->ShipSprite.setPosition(Teams.at(i).Ships.at(j)->Position.x - Teams.at(0).Ships.at(0)->Position.x + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().x,
															   Teams.at(i).Ships.at(j)->Position.y - Teams.at(0).Ships.at(0)->Position.y + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().y); //Draw ships relitive to Players ship

			for (int k = 0; k < Teams.at(i).Ships.at(j)->Projectiles.size(); k++)
			{
				Teams.at(i).Ships.at(j)->Projectiles.at(k)->SpritePos = sf::Vector2f((Teams.at(i).Ships.at(j)->Projectiles.at(k)->Position.x - Teams.at(0).Ships.at(0)->Position.x + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().x),
																					(Teams.at(i).Ships.at(j)->Projectiles.at(k)->Position.y - Teams.at(0).Ships.at(0)->Position.y + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().y)); //Draw provectiles relitive to Players ship

				if (Teams.at(i).Ships.at(j)->Projectiles.at(k)->Position.x + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().x < 0)
				{
					Teams.at(i).Ships.at(j)->Projectiles.erase(Teams.at(i).Ships.at(j)->Projectiles.begin() + k);   // Despawn bullets if off the side of the map
					break;
				}

				if (Teams.at(i).Ships.at(j)->Projectiles.at(k)->Position.y + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().y < 0)
				{
					Teams.at(i).Ships.at(j)->Projectiles.erase(Teams.at(i).Ships.at(j)->Projectiles.begin() + k);
					break;
				}

				if (Teams.at(i).Ships.at(j)->Projectiles.at(k)->Position.x + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().x > 1920 * (MapSize + 1))
				{
					Teams.at(i).Ships.at(j)->Projectiles.erase(Teams.at(i).Ships.at(j)->Projectiles.begin() + k);
					break;
				}

				if (Teams.at(i).Ships.at(j)->Projectiles.at(k)->Position.y + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().y > 1080 * (MapSize + 1))
				{
					Teams.at(i).Ships.at(j)->Projectiles.erase(Teams.at(i).Ships.at(j)->Projectiles.begin() + k);
					break;
				}
			}
		}
	}

	for (int i = 0; i < Teams.size(); i++)
	{
		if (i == 0)
			Teams.at(i).Update(pTime, MapSize, true); //This is the players team
		else
			Teams.at(i).Update(pTime, MapSize, false); //all the other teams
	}

	BackgroundSprite.setPosition(int(-Teams.at(0).Ships.at(0)->ShipSprite.getPosition().x + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().x) % 200 - 200, int(-Teams.at(0).Ships.at(0)->ShipSprite.getPosition().y + Teams.at(0).Ships.at(0)->ShipSprite.getPosition().y) % 200 - 200); //Some maths


	for (int i = 0; i < Teams.size(); i++)
	{
		for (int j = 0; j < Teams.at(i).Ships.size(); j++)
		{
			if ((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().x < 0) && (Teams.at(i).Ships.at(j)->Velocity.x < 0))
			{
				Teams.at(i).Ships.at(j)->Velocity.x = -(Teams.at(i).Ships.at(j)->Velocity.x * 0.2);
				Teams.at(i).Ships.at(j)->Velocity.y = (Teams.at(i).Ships.at(j)->Velocity.y * 0.5);  //Ship - map boundery colision detection
			}

			if ((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().x > 1920) && (Teams.at(i).Ships.at(j)->Velocity.x > 0))
			{
				Teams.at(i).Ships.at(j)->Velocity.x = -(Teams.at(i).Ships.at(j)->Velocity.x * 0.2);
				Teams.at(i).Ships.at(j)->Velocity.y = (Teams.at(i).Ships.at(j)->Velocity.y * 0.5);
			}

			if ((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().y < 0) && (Teams.at(i).Ships.at(j)->Velocity.y < 0))
			{
				Teams.at(i).Ships.at(j)->Velocity.y = -(Teams.at(i).Ships.at(j)->Velocity.y * 0.2);
				Teams.at(i).Ships.at(j)->Velocity.x = (Teams.at(i).Ships.at(j)->Velocity.x * 0.5);
			}

			if ((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().y > 1080) && (Teams.at(i).Ships.at(j)->Velocity.y > 0))
			{
				Teams.at(i).Ships.at(j)->Velocity.y = -(Teams.at(i).Ships.at(j)->Velocity.y * 0.2);
				Teams.at(i).Ships.at(j)->Velocity.x = (Teams.at(i).Ships.at(j)->Velocity.x * 0.5);
			}
		}
	}

	ColisionDetection();
}

void GameEngine::ColisionDetection()
{
	for (int i = 0; i < Teams.size(); i++)
	{
		for (int j = 0; j < Teams.at(i).Ships.size(); j++)
		{
			for (int k = 0; k < Teams.at(i).Ships.at(j)->Projectiles.size(); k++)
			{
				for (int x = 0; x < Asteroids.size(); x++)
				{
					if (Asteroids.at(x).Sprite.getGlobalBounds().contains(Teams.at(i).Ships.at(j)->Projectiles.at(k)->SpritePos))
					{
						delete Teams.at(i).Ships.at(j)->Projectiles.at(k);
						Teams.at(i).Ships.at(j)->Projectiles.erase(Teams.at(i).Ships.at(j)->Projectiles.begin() + k);		  //Bullets - Asteriods colision detection (Rectangle - point detection)			
						break;	
					}
				}
			}
		}		
	}

	for (int i = 0; i < Teams.size(); i++)
	{
		for (int j = 0; j < Teams.at(i).Ships.size(); j++)
		{
			for (int k = 0; k < Asteroids.size(); k++)
			{
				if (Asteroids.at(k).Sprite.getGlobalBounds().contains(Teams.at(i).Ships.at(j)->ShipSprite.getPosition()))
				{
					if (Teams.at(i).Ships.at(j)->invincibility.getElapsedTime().asSeconds() > 1)
					{
						Teams.at(i).Ships.at(j)->Velocity = -(sf::Vector2f(Teams.at(i).Ships.at(j)->Velocity.x * 0.2, Teams.at(i).Ships.at(j)->Velocity.y * 0.2)); //Ships - Asteriods colision detection (Rectangle - point detection)
						Teams.at(i).Ships.at(j)->invincibility.restart();
						break;
					}
				}
			}
		}
	}

	for (int x = 0; x < Teams.size(); x++)
	{
		for (int y = 0; y < Teams.at(x).Ships.size(); y++)
		{
			for (int i = 0; i < Teams.size(); i++)
			{
				for (int j = 0; j < Teams.at(i).Ships.size(); j++)
				{
					for (int k = 0; k < Teams.at(i).Ships.at(j)->Projectiles.size(); k++)
					{
						if (x != i)
						{
							if (Teams.at(x).Ships.at(y)->ShipSprite.getGlobalBounds().contains(Teams.at(i).Ships.at(j)->Projectiles.at(k)->SpritePos))
							{
								Teams.at(x).Ships.at(y)->Damage(Teams.at(i).Ships.at(j)->Projectiles.at(k)->Damage);              //Bullets - Ships colision detection (Rectangle - point detection)
								delete Teams.at(i).Ships.at(j)->Projectiles.at(k);
								Teams.at(i).Ships.at(j)->Projectiles.erase(Teams.at(i).Ships.at(j)->Projectiles.begin() + k);
							}
						}
					}
				}
			}
		}
	}
}


void GameEngine::Render(sf::RenderWindow* pTarget, bool IsUpPressed)
{
	pTarget->clear();

	pTarget->draw(BackgroundSprite);

	for (int i = 0; i < Teams.size(); i++)
	{
		Teams.at(i).Render(pTarget, IsUpPressed);
	}

	for (int i = 0; i < Asteroids.size(); i++)
	{
		pTarget->draw(Asteroids.at(i).Sprite);
	}

	pTarget->display();
}

void GameEngine::GenerateMap()
{
	
	Asteroid Temp;
	for (int i = 0; i < ((MapSize) * (MapSize) * 15); i++) 
	{		
		if (Temp.Generate(sf::Vector2f(rand() % int((1920 * (MapSize) / 2)), (rand() % int(1080 * (MapSize) / 2)))))
		{
			Asteroids.push_back(Temp);		
		}
	}
	Asteroids.shrink_to_fit();
	
}

bool GameEngine::CheckCross(sf::Vector2f Point1, sf::Vector2f Point2, sf::Vector2f Point3, sf::Vector2f Point4)
{																	//SFML Vectors are great for readability 
	float Grad1;													//Rules are in form y = mX + b 
	float Grad2;													//Grad = m
	float Yinter1;													//Yinter = b
	float Yinter2;

	bool IsAbove1;													//If bool = true, point lies above alternate line
	bool IsAbove2;													//If bool = false, point lies below alternate line
	bool IsAbove3;
	bool IsAbove4;

	bool OppositeSides1;											//If bool = true, points 1 and 2 are on either side of rule2
	bool OppositeSides2;											//If bool = true, points 3 and 4 are on either side of rule1

	Grad1 = (Point1.y - Point2.y) / (Point1.x - Point2.x);			//Rise over run to calculate graidiant
	Grad2 = (Point3.y - Point4.y) / (Point3.x - Point4.x); 			//Same for other line

	Yinter1 = (Point1.y - (Grad1 * Point1.x));						//Finding out how much Point1 lies above or
	Yinter2 = (Point3.y - (Grad2 * Point3.x));					    //below line with b = 0. This can give me the value for b.

	if (Point1.y > ((Grad2 * Point1.x) + Yinter2))					//Could do these steps in one line but space
		IsAbove1 = true;											//it out for readability
	else
		IsAbove1 = false;

	if (Point2.y > ((Grad2 * Point2.x) + Yinter2))					//What I'm doing is seeing if the Y value for
		IsAbove2 = true;											//a point is greater or less than the Y value
	else
		IsAbove2 = false;

	if (Point3.y > ((Grad1 * Point3.x) + Yinter1))
		IsAbove3 = true;
	else
		IsAbove3 = false;

	if (Point4.y > ((Grad1 * Point4.x) + Yinter1))
		IsAbove4 = true;											//for the rule when the X value for the point is subed into the rule. This telles me if
	else
		IsAbove4 = false;											//the point is above or below the line.			    

	if (IsAbove1 != IsAbove2)										//Are the points on opposite sides of the line
		OppositeSides1 = true;										//or same side? That is what in cheching here
	else
		OppositeSides1 = false;

	if (IsAbove3 != IsAbove4)										//And for the other 2 points
		OppositeSides2 = true;
	else
		OppositeSides2 = false;

	if (OppositeSides2 == true && OppositeSides1 == true)			//Is both OppisiteSides1 and 2 true?
		return true;												//Lines cross :)
	else
		return false;												//They dont :(
}

/*

float Angle = ((atan2f(((Teams.at(i).Ships.at(j)->ShipSprite.getPosition().y - Closestship->ShipSprite.getPosition().y)), (Teams.at(i).Ships.at(j)->ShipSprite.getPosition().x - Closestship->ShipSprite.getPosition().x))) * 180 / 3.1415926535);

if (Angle < 0)
{
Angle += 360;
}

if (ShipsInLos.size() >= 1)
{
if ((Angle < (Teams.at(i).Ships.at(j)->Direction + 90 + 5)) && (Angle >(Teams.at(i).Ships.at(j)->Direction + 90 - 5)))
{
Teams.at(i).Ships.at(j)->MoveDecide(pTime, 2);
}
else
{
if ((Angle - (Teams.at(i).Ships.at(j)->Direction + 90)) > 0)
{
Teams.at(i).Ships.at(j)->MoveDecide(pTime, 1);
}
else
{
Teams.at(i).Ships.at(j)->MoveDecide(pTime, 0);
}
}
}
*/