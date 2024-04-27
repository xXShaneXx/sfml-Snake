#ifndef SNAKE_H
#define SNAKE_H

#include<vector>
#include <SFML/Graphics.hpp>
#include "GameWindow.h"

class GameWindow;

enum direction
{
	up,
	down,
	right,
	left
};

struct SnakePart
{
	sf::Vector2f position;
	sf::Sprite bodySprite;
};

class Snake
{
	std::vector<SnakePart>parts;
	sf::Texture head;
	sf::Texture body;
	short int textureSize;

public:
	Snake(int size = 3, float x = 0, float y = 0);

	void Move(sf::Vector2f dir);

	void AddBody(sf::Vector2f);

	void Kill();


	friend void GameWindow::draw(const Snake& snake);

	friend class GameEngine;
};

#endif // !SNAKE_H
