#include "Apple.h"

Apple::Apple(int xx, int yy, Applecolor color): x{xx}, y{yy}
{
	switch (color)
	{
	case Apple::red:
		appleTexture.loadFromFile("Textures\\apple_red_32.png");
			break;
	case Apple::green:
		appleTexture.loadFromFile("Textures\\apple_green_32.png");
		break;
	default:
		appleTexture.loadFromFile("Textures\\apple_red_32.png");
		break;
	}
	appleTexture.setSmooth(true);

	appleSprite.setTexture(appleTexture);
	appleSprite.setPosition(sf::Vector2f(xx, yy));
}

sf::Vector2f Apple::getPosition()
{
	return sf::Vector2f(x, y);
}

void Apple::changePosition(int xx, int yy)
{
	x = xx;
	y = yy;

	appleSprite.setPosition(sf::Vector2f(x, y));
}