
#include "Asteroid.h"
#include <stdlib.h>

Asteroid::Asteroid()
{

}


Asteroid::~Asteroid()
{
}

bool Asteroid::Generate(sf::Vector2f pPosition)
{
	Position = pPosition;            //Complicated stuff ahead ;)

	int RandRotate = 0;              //A colective total of the current rotation from position for the next point
	int RandDistance = 0;            //Random distance center
	int PointNum = 0;                //What point am i up to?
	int PointCount = rand() % 4 + 4; //How many points do i want (between 4-8)

	Sprite.setPointCount(PointCount);

	for (int i = 0; i < PointCount; i++)
	{
		RandDistance = rand() % 30 + 50;  //between (30-80)

		Sprite.setPoint(PointNum, sf::Vector2f((cos((RandRotate)* 3.1415926535 / 180.0) * RandDistance) + pPosition.x, (sin((RandRotate)* 3.1415926535 / 180.0) * RandDistance) + pPosition.y));  //fancy trig calculations and radian/degree convertions

		int MaxCheck = 1000;  //on rare occurences (i never knew why) not giving up after 1000 trys caused crashing. Imposible configurations?
		int CheckCount = 0;

		while (i > 2 && (!(ConvexCheck(Sprite.getPoint(i), Position, Sprite.getPoint(i - 2), Sprite.getPoint(i - 1)))) && CheckCount < MaxCheck) //(i > 2) so i dont access a element out of range. basicly is keeps trying until the point makes a convex poligon
		{
			RandDistance = rand() % 30 + 50;
			Sprite.setPoint(PointNum, sf::Vector2f((cos((RandRotate)* 3.1415926535 / 180.0) * RandDistance) + pPosition.x, (sin((RandRotate)* 3.1415926535 / 180.0) * RandDistance) + pPosition.y));
			CheckCount++;
		}

		if (CheckCount == 1000)
			return false;       //Poligon failed to generate.

		if (360 - RandRotate < PointCount - i)  //to avoid a divide by 0 error later
		{
			Sprite.setPointCount(i);
			if (Sprite.getPointCount() < 4)
			{
				return false;    //not enough sides for my liking. The GameEngine will delete this asteroid and try again.
			}
			break;
		}

		RandRotate += rand() % ((360 - RandRotate) / (PointCount - i)) + 30; // (remaining degrees) / (remaining points) + 30 

		if (RandRotate >= 360) //I had this here a long time ago but cant prove if i need it ;P
		{
			Sprite.setPointCount(i);
			if (Sprite.getPointCount() < 4)
			{
				return false;
			}
			break;
		}
		PointNum++;
	}

	Sprite.setFillColor(sf::Color(64, 64, 64, 255)); //Gray insides
	Sprite.setOutlineColor(sf::Color::White); //white boarder
	Sprite.setOutlineThickness(1);

	if ((ConvexCheck(Sprite.getPoint(1), Position, Sprite.getPoint(Sprite.getPointCount() - 1), Sprite.getPoint(0))) == false)
	{
		return false;  //Havent checked points 1, and 0 due to above code (i > 2). Checking them now for concave poligon.
	}

	if ((ConvexCheck(Sprite.getPoint(0), Position, Sprite.getPoint(Sprite.getPointCount() - 2), Sprite.getPoint(Sprite.getPointCount() - 1))) == false)
	{
		return false;
	}


	return true; //Poligon was convex :) (On very, like 1/2000, a concave poligon is returned. cant find why.
}

bool Asteroid::ConvexCheck(sf::Vector2f Point1, sf::Vector2f Point2, sf::Vector2f Point3, sf::Vector2f Point4)
{
	float Grad1;
	float Yinter1;

	bool IsAbove1;
	bool IsAbove2;

	if ((Point3.x - Point4.x) != 0)
		Grad1 = (Point3.y - Point4.y) / (Point3.x - Point4.x);
	else
		return false;

	Yinter1 = (Point3.y - (Grad1 * Point3.x));

	if (Point1.y > ((Grad1 * Point1.x) + Yinter1))
		IsAbove1 = true;
	else
		IsAbove1 = false;

	if (Point2.y > ((Grad1 * Point2.x) + Yinter1))
		IsAbove2 = true;
	else
		IsAbove2 = false;

	if (IsAbove1 == IsAbove2)
		return true;
	else
		return false;
}