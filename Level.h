#pragma once
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Level {
	public:
		Level();
		~Level() {}

		void Process();
		void Draw();

		bool Completed() { return currentScreen == scr_completed; }

	protected:
		enum Screen { scr_first, scr_second, scr_third, scr_completed }; // 3 per level (1 to 3, 4 = completed)
		Screen currentScreen;

		virtual void loadScreen() = 0;
		
		bool answerCorrect = false;

		struct Figure {
			Figure(sf::Shape* a, sf::Shape* b)
			{
				firstShape = a, secondShape = b;
				has2Shapes = (b != nullptr);
			}
			sf::Shape* firstShape;
			sf::Shape* secondShape;
			bool has2Shapes;
		};
		std::vector<Figure> statement;
		std::vector<Figure> options;
		int correctAnswer;
		int attempts;

		// shapes
		sf::CircleShape triangle;
		sf::CircleShape circle;
		sf::RectangleShape line;
		sf::RectangleShape rectangle;
		sf::CircleShape romboid;

		// Text
		sf::Font arial;
		sf::Text scoreText;
		sf::Text textAttempts;
		sf::Text levelText;
};

inline Level::Level()
{
	arial.loadFromFile("Arial.ttf");
	scoreText.setFont(arial);
	scoreText.setPosition(Game::GetWindow()->getView().getSize().x * 0.9f, 100.f);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setCharacterSize(30);

	textAttempts.setFont(arial);
	textAttempts.setPosition(Game::GetWindow()->getView().getSize().x * 0.9f, 140.f);
	textAttempts.setFillColor(sf::Color::Black);
	textAttempts.setCharacterSize(30);

	levelText.setFont(arial);
	levelText.setPosition(50.f, 50.f);
	levelText.setFillColor(sf::Color::Black);
	levelText.setCharacterSize(30);

	currentScreen = scr_first;
	attempts = 0;

	int size = 60;

	triangle = sf::CircleShape(size, 3);
	triangle.setFillColor(sf::Color::Yellow);
	triangle.setOrigin(triangle.getLocalBounds().width / 2.f, triangle.getLocalBounds().height);

	circle = sf::CircleShape(size);
	circle.setFillColor(sf::Color::Red);
	circle.setOrigin(circle.getLocalBounds().width / 2.f, circle.getLocalBounds().height);

	line = sf::RectangleShape(sf::Vector2f(size, 5));
	line.setOrigin(line.getLocalBounds().width / 2.f, line.getLocalBounds().height);
	line.setFillColor(sf::Color::Black);

	rectangle = sf::RectangleShape(sf::Vector2f(size * 2, size));
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setOrigin(rectangle.getLocalBounds().width / 2.f, rectangle.getLocalBounds().top + size);

	romboid = sf::CircleShape(size, 6);
	romboid.setFillColor(sf::Color::Cyan);
	romboid.setOrigin(romboid.getLocalBounds().width / 2.f, romboid.getLocalBounds().height);
}

inline void Level::Process()
{
	sf::Event e;
	while (Game::GetWindow()->pollEvent(e)) {
		if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			Game::GetWindow()->close();

		if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left) {
			int x = sf::Mouse::getPosition(*Game::GetWindow()).x;
			int y = sf::Mouse::getPosition(*Game::GetWindow()).y;

			if (!answerCorrect) {
				for (int i = 0; i < options.size(); i++) {
					if (options[i].firstShape->getGlobalBounds().contains(x, y)) {
						attempts++;
						if (i == correctAnswer) {
							answerCorrect = true;
							Game::score += 10;
						}
					}
				}
			}
			else {
				if (Game::nextScreen.getGlobalBounds().contains(x, y)) {
					switch (currentScreen)
					{
					case Level::scr_first: currentScreen = scr_second; break;
					case Level::scr_second:	currentScreen = scr_third; break;
					case Level::scr_third: currentScreen = scr_completed; break;
					default:
						break;
					}
					loadScreen();
					answerCorrect = false;
				}
			}
		}
	}
}

inline void Level::Draw()
{
	int xOffset = 200;
	int yOffset = 200;

	for (int i = 0; i < statement.size(); i++) {
		statement[i].firstShape->setPosition((i + 1) * xOffset, yOffset);
		Game::GetWindow()->draw(*statement[i].firstShape);
		if (statement[i].has2Shapes) {
			statement[i].secondShape->setPosition((i + 1) * xOffset, yOffset);
			statement[i].secondShape->setScale(0.8f, 0.8f); // smaller
			Game::GetWindow()->draw(*statement[i].secondShape);
		}
	}

	yOffset = 500;
	for (int i = 0; i < options.size(); i++) {
		options[i].firstShape->setPosition((i + 1) * xOffset, yOffset);
		Game::GetWindow()->draw(*options[i].firstShape);
		if (options[i].has2Shapes) {
			options[i].secondShape->setPosition((i + 1) * xOffset, yOffset);
			statement[i].secondShape->setScale(0.8f, 0.8f); // smaller
			Game::GetWindow()->draw(*options[i].secondShape);
		}
	}

	Game::GetWindow()->draw(levelText);

	scoreText.setString("Score: " + std::to_string(Game::score));
	Game::GetWindow()->draw(scoreText);
	textAttempts.setString("Attempts: " + std::to_string(attempts));
	Game::GetWindow()->draw(textAttempts);

	if (answerCorrect) {
		Game::GetWindow()->draw(Game::nextScreen);
	}
}