#pragma once

#include "Level.h"

class LevelThree : public Level
{
public:
	LevelThree();
	~LevelThree() {}

private:
	void loadScreen();

	sf::RectangleShape lineUp;
	sf::RectangleShape lineDiagonal;
	sf::RectangleShape halfLine;
	sf::RectangleShape halfLineDiagonal;
	sf::RectangleShape halfLineDiagonal2;
	sf::ConvexShape convex;
};