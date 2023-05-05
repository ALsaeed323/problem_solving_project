#include "LevelOne.h"

LevelOne::LevelOne()
{
	levelText.setString("Level 1:");
	loadScreen();
}

void LevelOne::loadScreen()
{
	statement.clear();
	options.clear();
	attempts = 0;

	switch (Level::currentScreen)
	{
	case Level::scr_first: {
		/// STATEMENTS
		statement.push_back(Figure(&triangle, nullptr));
		statement.push_back(Figure(&circle, nullptr));
		statement.push_back(Figure(&triangle, nullptr));
		statement.push_back(Figure(&line, nullptr));
		/// OPTIONS
		options.push_back(Figure(&rectangle, nullptr)); // 0
		options.push_back(Figure(&rectangle, nullptr)); // 1
		options.push_back(Figure(&circle, nullptr)); // 2
		correctAnswer = 2;
	} break;
	case Level::scr_second: {
		/// STATEMENTS
		statement.push_back(Figure(&rectangle, nullptr));
		statement.push_back(Figure(&triangle, nullptr));
		statement.push_back(Figure(&line, nullptr));
		statement.push_back(Figure(&triangle, nullptr));
		/// OPTIONS
		options.push_back(Figure(&rectangle, nullptr)); // 0
		options.push_back(Figure(&triangle, nullptr)); // 1
		options.push_back(Figure(&circle, nullptr)); // 2
		correctAnswer = 0;
	} break;
	case Level::scr_third: {
		/// STATEMENTS
		statement.push_back(Figure(&rectangle, nullptr));
		statement.push_back(Figure(&rectangle, nullptr));
		statement.push_back(Figure(&circle, nullptr));
		statement.push_back(Figure(&line, nullptr));
		/// OPTIONS
		options.push_back(Figure(&triangle, nullptr)); // 0
		options.push_back(Figure(&rectangle, nullptr)); // 1
		options.push_back(Figure(&circle, nullptr)); // 2
		correctAnswer = 2;
	} break;
	default: //std::cout << "ERROR - "
		break;
	}
}
