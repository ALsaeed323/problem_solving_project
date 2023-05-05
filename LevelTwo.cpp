#include "LevelTwo.h"


LevelTwo::LevelTwo()
{
	levelText.setString("Level 2:");

	loadScreen();
}

void LevelTwo::loadScreen()
{
	statement.clear();
	options.clear();
	attempts = 0;

	switch (Level::currentScreen)
	{
	case Level::scr_first: {
		/// STATEMENTS
		statement.push_back(Figure(&rectangle, &circle));
		statement.push_back(Figure(&rectangle, nullptr));
		statement.push_back(Figure(&line, nullptr));
		/// OPTIONS
		options.push_back(Figure(&circle, nullptr)); // 0
		options.push_back(Figure(&rectangle, nullptr)); // 1
		options.push_back(Figure(&rectangle, nullptr)); // 2
		correctAnswer = 0;
	} break;
	case Level::scr_second: {
		/// STATEMENTS
		statement.push_back(Figure(&circle, &triangle));
		statement.push_back(Figure(&line, nullptr));
		statement.push_back(Figure(&triangle, nullptr));
		/// OPTIONS
		options.push_back(Figure(&triangle, nullptr)); // 0
		options.push_back(Figure(&circle, nullptr)); // 1
		options.push_back(Figure(&romboid, nullptr)); // 2
		correctAnswer = 1;
	} break;
	case Level::scr_third: {
		/// STATEMENTS
		statement.push_back(Figure(&line, nullptr));
		statement.push_back(Figure(&circle, nullptr));
		statement.push_back(Figure(&triangle, &circle));
		/// OPTIONS
		options.push_back(Figure(&circle, nullptr)); // 0
		options.push_back(Figure(&triangle, nullptr)); // 1
		options.push_back(Figure(&rectangle, nullptr)); // 2
		correctAnswer = 1;
	} break;
	default: //std::cout << "ERROR - "
		break;
	}
}
