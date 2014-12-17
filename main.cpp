#include "GameEngine.h"

sf::RenderWindow window;

sf::Clock GameClock;

void PollEvent(GameEngine*);
void Update(GameEngine*);
void Render(GameEngine*, bool);


sf::Time PrevTime;

bool UpPressed;
bool LeftPressed;
bool RightPressed;
bool LeftMousePressed;
bool RightMousePressed;


int main()
{
	srand(time(NULL));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.setVerticalSyncEnabled(true);
	window.create(sf::VideoMode(1920, 1080), "Asteriod Wars", sf::Style::Default, settings);

	GameClock.restart();

	GameEngine Game1(&window);

	Game1.BackgroundTex.setRepeated(true);//
	Game1.BackgroundTex.loadFromFile("StarBackground.jpg");//
	Game1.BackgroundSprite.setTexture(Game1.BackgroundTex);//
	Game1.MapSize = 2;//

	PlayerShip* MyShip1;
	AIShip* MyShip2;
	AIShip* MyShip3;
	AIShip* MyShip4;
	AIShip* MyShip5;
	AIShip* MyShip6;
	AIShip* MyShip7;
	AIShip* MyShip8;
	AIShip* MyShip9;


	MyShip1 = new PlayerShip();
	MyShip2 = new AIShip();
	MyShip3 = new AIShip();
	MyShip4 = new AIShip();
	MyShip5 = new AIShip();
	MyShip6 = new AIShip();
	MyShip7 = new AIShip();
	MyShip8 = new AIShip();
	MyShip9 = new AIShip();




	Game1.AddTeam(sf::Color(255, 128, 0, 255));
	Game1.AddTeam(sf::Color(128, 0, 255, 255));
	Game1.AddTeam(sf::Color(0, 255, 0, 255));

	Game1.Teams.at(0).AddShip(MyShip1, Game1.MapSize);
	Game1.Teams.at(0).AddShip(MyShip2, Game1.MapSize);
	Game1.Teams.at(0).AddShip(MyShip3, Game1.MapSize);
	Game1.Teams.at(1).AddShip(MyShip4, Game1.MapSize);
	Game1.Teams.at(1).AddShip(MyShip5, Game1.MapSize);
	Game1.Teams.at(1).AddShip(MyShip6, Game1.MapSize);
	Game1.Teams.at(2).AddShip(MyShip7, Game1.MapSize);
	Game1.Teams.at(2).AddShip(MyShip8, Game1.MapSize);
	Game1.Teams.at(2).AddShip(MyShip9, Game1.MapSize);

	
	Game1.GenerateMap();

	while (true)
	{
		if (GameClock.getElapsedTime().asSeconds() > (1/60))
		{
			PollEvent(&Game1);

			Update(&Game1);

			Render(&Game1, UpPressed);

			PrevTime = GameClock.getElapsedTime();
			GameClock.restart();
		}
	}
}

void Render(GameEngine* pEngine, bool IsUpPressed)
{
	pEngine->Render(&window, UpPressed);
}



void Update(GameEngine* pEngine)
{
	pEngine->Update(PrevTime);
	
	if (UpPressed)
		pEngine->Teams.at(0).Ships.at(0)->Accelerate(PrevTime);
	if (LeftPressed)
		pEngine->Teams.at(0).Ships.at(0)->TurnLeft(PrevTime);
	if (RightPressed)
		pEngine->Teams.at(0).Ships.at(0)->TurnRight(PrevTime);
	if (LeftMousePressed)
		pEngine->Teams.at(0).Ships.at(0)->Fire1();
	if (RightMousePressed)
		pEngine->Teams.at(0).Ships.at(0)->Fire2();
}

void PollEvent(GameEngine* pEngine)
{
	sf::Event event;
	
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			LeftMousePressed = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			pEngine->Teams.at(0).Ships.at(0)->Health = -1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			LeftPressed = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			RightPressed = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			UpPressed = true;
		}



		if (!(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		{
			LeftMousePressed = false;
		}

		if (!(sf::Mouse::isButtonPressed(sf::Mouse::Right)))
		{
			RightMousePressed = false;
		}

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			LeftPressed = false;
		}

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			RightPressed = false;
		}

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
		{
			UpPressed = false;
		}
	}
}
