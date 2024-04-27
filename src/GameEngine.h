#pragma once
#include "Snake.h"
#include "GameWindow.h"
#include "Apple.h"

class GameEngine
{
	GameWindow window;
	Snake snake;
	Apple apple;
	enum controls;
	sf::Vector2f moveDir;
	bool dirChanged;
	bool gameOver;
	int count;
	sf::Font font;
	sf::Text counter;
	

public:
	GameEngine(int windowWidth, int windowHeight, std::string name, int SnakeSize);

	void StartGame();

private:
	void checkButtons();

	void updateCounter();

	void Update(sf::Clock& clock);

	bool CheckIfHitWall();

	bool CheckIfHitItself();

	bool CheckIfHitApple();

	void CheckWin();
};
