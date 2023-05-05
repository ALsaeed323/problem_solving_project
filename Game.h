#pragma once

#include "SFML/Graphics.hpp"

class Textbox;
class LevelOne;
class LevelTwo;
class LevelThree;

class Game
{
public:
	static void Start();

	static int score;

	static sf::RenderWindow* GetWindow() { return &_mainWindow; }

	static sf::Sprite nextScreen;
private:
	~Game() {} // Destructors of Static Classes are never called

	static std::string currentUser;

	// Game
	static sf::RenderWindow _mainWindow;
	static sf::Clock _deltaClock;
	static sf::Time _deltaTime;
	static void GameLoop();

	static bool running;

	static sf::Sprite background;

	// Sprites for Login
	static sf::Sprite user;
	static sf::Sprite password;
	static sf::Sprite enter;
	static sf::Sprite parent;
	static sf::Sprite parentSelected;
	
	// Textboxes for Login
	static Textbox textLoginUsr;
	static Textbox textLoginPass;
	static Textbox textLoginEnter;

	static sf::Text textScores;

	// Levels
	static enum LevelNumber { lvl_one, lvl_two, lvl_three, completed };
	static LevelNumber currentLevel;
	static LevelOne lvl1;
	static LevelTwo lvl2;
	static LevelThree lvl3;
};