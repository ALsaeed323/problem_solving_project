#include "Game.h"

#include "TextBox.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"

#include <fstream>
#include "SFML/Graphics.hpp"

struct Clicked
{
	bool email = false;
	bool password = false;
};
Clicked clicked;

struct account
{
	std::string email;
	std::string password;
};


// SONS
int amountOfSons = 1;
account sons[100];
void loadSonsData()
{
	std::ifstream fin("sons.txt", std::ios::in | std::ios::out);
	while (fin >> sons[amountOfSons].email)
	{
		fin >> sons[amountOfSons].password;
		amountOfSons++;
	}
	fin.close();
}

// PARENTS
int amountOfParents = 1;
account parents[100];
void loadParentsData()
{
	std::ifstream fin("parents.txt", std::ios::in | std::ios::out);
	while (fin >> parents[amountOfParents].email)
	{
		fin >> parents[amountOfParents].password;
		amountOfParents++;
	}
	fin.close();
}

int amountOfScores = 1;
std::string scores[100];
void loadScores()
{
	std::ifstream sc("sons_scores.txt", std::ios::in | std::ios::out);
	while (sc >> scores[amountOfScores])
	{
		amountOfScores++;
	}
	sc.close();
}

void saveScores()
{
	std::ofstream sc("sons_scores.txt", std::ios::in | std::ios::out);	
	for (int i = 1; i < amountOfScores; i++) {
		sc << scores[i] << "\n";
	}
	sc.close();
}

void modifyScores(std::string _usr, int _score, float seconds)
{
	int i = 1;
	while (_usr != scores[i]) i++;
	scores[i + 1] = std::to_string(_score);
	scores[i + 2] = std::to_string(seconds);
}

bool loginSuccessful = false;

void Game::Start()
{
	_mainWindow.create(sf::VideoMode(1280, 720), "SFML HAZEM", sf::Style::Titlebar);
	
	sf::Texture t_bg, t_usr, t_pass, t_enter, t_parent, t_parentSelected, t_nextScreen;

	t_bg.loadFromFile("bg.png");
	background = sf::Sprite(t_bg);

	// textures for login
	t_usr.loadFromFile("user.png");
	t_pass.loadFromFile("Password.png");
	t_enter.loadFromFile("enter.png");
	t_parent.loadFromFile("parent.png");
	t_parentSelected.loadFromFile("parentSelected.png");

	// sprites for login
	user = sf::Sprite(t_usr);
	password = sf::Sprite(t_pass);
	enter = sf::Sprite(t_enter);
	parent = sf::Sprite(t_parent);
	parentSelected = sf::Sprite(t_parentSelected);

	// next screen button
	t_nextScreen.loadFromFile("next.png");
	nextScreen = sf::Sprite(t_nextScreen);
	nextScreen.setPosition(_mainWindow.getView().getSize().x * 0.7f, _mainWindow.getView().getSize().y * 0.6f);

	// font
	sf::Font arial;
	arial.loadFromFile("Arial.ttf");

	// Textboxs to input text
	textLoginUsr.setFont(arial);
	textLoginPass.setFont(arial);
	textLoginEnter.setFont(arial);

	textScores.setFont(arial);
	textScores.setFillColor(sf::Color::Black);
	textScores.setCharacterSize(30);

	loadSonsData();
	loadParentsData();
	loadScores();

	_deltaTime = _deltaClock.restart();

	// Game Loop
	while (true)
	{
		GameLoop();
	}

	// Close Game
	_mainWindow.close();
}

void Game::GameLoop()
{
	bool isParent = false;

	while (_mainWindow.isOpen()) {
		sf::Event e;

		if (!loginSuccessful) {
			while (_mainWindow.pollEvent(e)) {
				if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
					_mainWindow.close();
				if (e.type == sf::Event::MouseButtonPressed)
				{
					if (e.key.code == sf::Mouse::Left)
					{
						int x = sf::Mouse::getPosition(_mainWindow).x;
						int y = sf::Mouse::getPosition(_mainWindow).y;

						if (parent.getGlobalBounds().contains(x, y) || parentSelected.getGlobalBounds().contains(x, y))
						{
							isParent = !isParent;
						}
						if (user.getGlobalBounds().contains(x, y))
						{
							// click on email
							clicked.email = true;
							textLoginUsr.setSelected(true);
						}
						if (password.getGlobalBounds().contains(x, y))
						{
							//click on password
							clicked.password = true;
							textLoginPass.setSelected(true);
						}
						// submit
						if (enter.getGlobalBounds().contains(x, y))
						{
							std::string e, p;
							e = textLoginUsr.getText();
							p = textLoginPass.getText();
							if (e.empty() == false && p.empty() == false)
							{
								for (int j = 1; j <= amountOfSons; j++)
								{
									if (!isParent && e == sons[j].email && p == sons[j].password)
									{
										currentUser = e;
										loginSuccessful = true;
									}
									else if (isParent && e == parents[j].email && p == parents[j].password)
									{
										currentUser = e;
										loginSuccessful = true;
									}
								}
							}
						}
					}
				}
				if (e.type == sf::Event::TextEntered)
				{
					if (clicked.email == true)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						{
							textLoginUsr.setSelected(false);
							clicked.email = false;
						}
						else
						{
							textLoginUsr.typedOn(e);
						}
					}
					else if (clicked.password == true)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						{
							textLoginPass.setSelected(false);
							clicked.password = false;
						}
						else
						{
							textLoginPass.typedOn(e);
						}
					}
				}
			}

			// DRAW
			_mainWindow.clear();
			_mainWindow.draw(background);

			user.setPosition(50, 100);
			_mainWindow.draw(user);
			password.setPosition(50, 235);
			_mainWindow.draw(password);
			enter.setPosition(50, 405);
			_mainWindow.draw(enter);
			
			if (!isParent) {
				parent.setPosition(50, 20);
				_mainWindow.draw(parent);
			}
			else {
				parentSelected.setPosition(50, 20);
				_mainWindow.draw(parentSelected);
			}

			textLoginUsr.setPosition({ 70.f + (float)user.getTextureRect().width, 100 });
			textLoginUsr.drawTo(_mainWindow);
			textLoginPass.setPosition({ 70.f + (float)password.getTextureRect().width,237 });
			textLoginPass.drawTo(_mainWindow);

		}
		// GAME
		else {
			_mainWindow.clear();
			_mainWindow.draw(background);

			if (!isParent) {
				switch (currentLevel)
				{
				case Game::lvl_one: {
					lvl1.Process();
					if (lvl1.Completed()) currentLevel = lvl_two;
					lvl1.Draw();
					} break;
				case Game::lvl_two: {
					lvl2.Process();
					if (lvl2.Completed()) currentLevel = lvl_three;
					lvl2.Draw();
				} break;
				case Game::lvl_three: {
					lvl3.Process();
					if (lvl3.Completed()) {
						currentLevel = completed;
						_deltaTime = _deltaClock.restart();
						modifyScores(currentUser, score, _deltaTime.asSeconds());
						saveScores();
					}
					lvl3.Draw();
				} break;
				case Game::completed: {
					int i = 1;
					while (currentUser != scores[i]) i++;
					textScores.setString("Congratulations!\n\n\t" + scores[i] + "\n");
					textScores.setString(textScores.getString() + "\t\tScore : " + scores[i + 1] + "\n");
					textScores.setString(textScores.getString() + "\t\tSeconds: " + scores[i + 2] + "\n\n");
					_mainWindow.draw(textScores);
				} break;
				default:
					break;
				}
			}
			else {
				textScores.setString("\n\n");
				enum stringPart { usr, scr, time };
				stringPart part;
				part = usr;
				for (int i = 1; i < amountOfScores; i++) {
					if (part == usr) {
						textScores.setString(textScores.getString() + "\t" + scores[i] + "\n");
						part = scr;
					}
					else if (part == scr) {
						textScores.setString(textScores.getString() + "\t\tScore : " + scores[i] + "\n");
						part = time;
					}
					else if (part == time) {
						textScores.setString(textScores.getString() + "\t\tSeconds: " + scores[i] + "\n\n");
						part = usr;
					}
				}
				_mainWindow.draw(textScores);
			}
		}
		_mainWindow.display();
	}
}

int Game::score = 0;
std::string Game::currentUser;

// Game
sf::RenderWindow Game::_mainWindow;
sf::Clock Game::_deltaClock; // starts the clock
sf::Time Game::_deltaTime;

sf::Sprite Game::background;

sf::Sprite Game::user;
sf::Sprite Game::password;
sf::Sprite Game::enter;
sf::Sprite Game::parent;
sf::Sprite Game::parentSelected;

sf::Sprite Game::nextScreen;

Textbox Game::textLoginUsr(30, sf::Color::Black, false);
Textbox Game::textLoginPass(30, sf::Color::Black, false);
Textbox Game::textLoginEnter(30, sf::Color::Black, false);

sf::Text Game::textScores;

Game::LevelNumber Game::currentLevel;
LevelOne Game::lvl1;
LevelTwo Game::lvl2;
LevelThree Game::lvl3;
