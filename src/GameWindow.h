#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H


#include <SFML/Graphics.hpp>
#include <vector>

class Snake;
class Apple;
class GameWindow : public sf::RenderWindow
{
	sf::Texture grassTexture;
	sf::Texture wallTexture;

	sf::Sprite grassSprite;
	std::vector<sf::Sprite> wallSprites;

public:
	short int grassSize;
	short int wallSize;

	using sf::RenderWindow::RenderWindow;

	void init();

	void draw(const Snake& snake);

	void draw(const Apple& apple);

	void drawBackground();
};

#endif // !GAMEWINDOW_H
