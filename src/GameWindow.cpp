#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "Snake.h"
#include "Apple.h"

void GameWindow::draw(const Snake& snake)
{
	for(auto const &part : snake.parts)
		(*this).sf::RenderWindow::draw(part.bodySprite);
}

void GameWindow::draw(const Apple& apple)
{
	(*this).sf::RenderWindow::draw(apple.appleSprite);
}

void GameWindow::init()
{
	grassTexture.loadFromFile("Textures\\grass64.png");
	grassTexture.setSmooth(true);
	grassTexture.setRepeated(true);
	grassSize = grassTexture.getSize().x;

	grassSprite.setTexture(grassTexture);
	grassSprite.setTextureRect((*this).getViewport((*this).getDefaultView()));

	wallTexture.loadFromFile("Textures\\wall_block_32_0.png");
	wallTexture.setRepeated(true);
	wallSize = wallTexture.getSize().x;

	wallSprites.resize(4);
	for (auto& wall : wallSprites)
		wall.setTexture(wallTexture);

	wallSprites[0].setTextureRect({ 0, 0, static_cast<int>(getSize().x), 32 });
	wallSprites[1].setTextureRect({ 0, 0, static_cast<int>(getSize().x), 32 });
	wallSprites[1].setPosition(0, static_cast<int>(getSize().y) - 32);

	wallSprites[2].setTextureRect({ 0, 0, 32, static_cast<int>(getSize().y) });
	wallSprites[3].setTextureRect({ 0, 0, 32, static_cast<int>(getSize().y) });
	wallSprites[3].setPosition(static_cast<int>(getSize().x) - 32, 0);

	(*this).setFramerateLimit(60);
}

void GameWindow::drawBackground()
{
	sf::RenderWindow::draw(grassSprite);

	for (auto& wall : wallSprites)
		(*this).sf::RenderWindow::draw(wall);
}