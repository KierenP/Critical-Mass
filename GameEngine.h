#pragma once
#include "Asteroid.h"
#include "Team.h"

class GameEngine
{
public:
	GameEngine(sf::RenderWindow*);
	~GameEngine();
	sf::Texture BackgroundTex; 
	sf::Sprite BackgroundSprite; //The stars you see
	int MapSize = 2;             //How big is the map?
	vector<Asteroid> Asteroids;  
	vector<Team> Teams;          
	void GenerateMap();          
	void AddTeam(sf::Color);
	void Update(sf::Time);
	void Render(sf::RenderWindow*, bool);
	void ColisionDetection();
	void AiMoveDecide(sf::Time);
	bool CheckCross(sf::Vector2f Point1, sf::Vector2f Point2, sf::Vector2f Point3, sf::Vector2f Point4);
};

