#include "LevelThree.h"

LevelThree::LevelThree()
{
	levelText.setString("Level 3:");

	int size = 60;

	lineUp = sf::RectangleShape(sf::Vector2f(size, 5));
	lineUp.setOrigin(lineUp.getLocalBounds().width / 2.f, lineUp.getLocalBounds().height);
	lineUp.setRotation(90.f);
	lineUp.setFillColor(sf::Color::Black);

	lineDiagonal = sf::RectangleShape(sf::Vector2f(size, 5));
	lineDiagonal.setOrigin(lineDiagonal.getLocalBounds().width / 2.f, lineDiagonal.getLocalBounds().height);
	lineDiagonal.setRotation(-45.f);
	lineDiagonal.setFillColor(sf::Color::Black);

	halfLine = sf::RectangleShape(sf::Vector2f(size / 2.f, 5));
	halfLine.setOrigin(halfLine.getLocalBounds().width / 2.f, halfLine.getLocalBounds().height);
	halfLine.setFillColor(sf::Color::Black);

	halfLineDiagonal = sf::RectangleShape(sf::Vector2f(size / 2.f, 5));
	halfLineDiagonal.setOrigin(halfLineDiagonal.getLocalBounds().width / 2.f, halfLineDiagonal.getLocalBounds().height);
	halfLineDiagonal.setRotation(-45.f);
	halfLineDiagonal.setFillColor(sf::Color::Black);

	halfLineDiagonal2 = sf::RectangleShape(sf::Vector2f(size / 2.f, 5));
	halfLineDiagonal2.setOrigin(halfLineDiagonal2.getLocalBounds().width / 2.f, halfLineDiagonal2.getLocalBounds().height);
	halfLineDiagonal2.setRotation(-135.f);
	halfLineDiagonal2.setFillColor(sf::Color::Black);

	convex.setPointCount(3);

	// define the points
	convex.setPoint(0, sf::Vector2f(0, 0));
	convex.setPoint(1, sf::Vector2f(120, 0));
	convex.setPoint(2, sf::Vector2f(0, 60));
	convex.rotate(180);
	convex.setFillColor(sf::Color::Black);

	loadScreen();
}

void LevelThree::loadScreen()
{
	statement.clear();
	options.clear();
	attempts = 0;

	switch (Level::currentScreen)
	{
	case Level::scr_first: {
		/// STATEMENTS
		statement.push_back(Figure(&lineUp, nullptr));
		statement.push_back(Figure(&lineUp, nullptr));
		statement.push_back(Figure(&line, nullptr));
		statement.push_back(Figure(&line, nullptr));
		/// OPTIONS
		options.push_back(Figure(&triangle, nullptr)); // 0
		options.push_back(Figure(&circle, nullptr)); // 1
		options.push_back(Figure(&rectangle, nullptr)); // 2
		correctAnswer = 2;
	} break;
	case Level::scr_second: {
		/// STATEMENTS
		statement.push_back(Figure(&lineUp, nullptr));
		statement.push_back(Figure(&lineDiagonal, nullptr));
		statement.push_back(Figure(&line, nullptr));
		/// OPTIONS
		options.push_back(Figure(&triangle, nullptr)); // 0
		options.push_back(Figure(&rectangle, nullptr)); // 1
		options.push_back(Figure(&convex, nullptr)); // 2
		correctAnswer = 2;
	} break;
	case Level::scr_third: {
		/// STATEMENTS
		statement.push_back(Figure(&halfLine, nullptr));
		statement.push_back(Figure(&halfLineDiagonal, nullptr));
		statement.push_back(Figure(&halfLineDiagonal2, nullptr));
		statement.push_back(Figure(&halfLine, nullptr));
		/// OPTIONS
		options.push_back(Figure(&triangle, nullptr)); // 0
		options.push_back(Figure(&circle, nullptr)); // 1
		options.push_back(Figure(&romboid, nullptr)); // 2
		correctAnswer = 2;
	} break;
	default: //std::cout << "ERROR - "
		break;
	}
}
