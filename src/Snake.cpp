#include"Snake.h"

Snake::Snake(int size, float x, float y)
{
	head.loadFromFile("Textures\\snake_green_head_32.png");
	head.setSmooth(true);

	body.loadFromFile("Textures\\snake_green_blob_32.png");
	body.setSmooth(true);
	
	textureSize = body.getSize().x;

	parts.resize(size);
	parts[0].position = sf::Vector2f(x ,y);
	parts[0].bodySprite.setTexture(head);
	parts[0].bodySprite.setPosition(sf::Vector2f(x, y));

	for (int i = 1; i < size; i++)
	{
		parts[i].bodySprite.setTexture(body);
		parts[i].position = sf::Vector2f(parts[i - 1].position.x - textureSize, parts[i - 1].position.y);

		parts[i].bodySprite.setPosition(parts[i].position);
	}

}

void Snake::Move(sf::Vector2f dir)
{
	for (int i = parts.size() - 1; i > 0; i--)
	{
		parts[i].position = parts[i - 1].position;
		parts[i].bodySprite.setPosition(parts[i].position);
	}

	parts[0].position.y += dir.y * textureSize;
	parts[0].position.x += dir.x * textureSize;

	parts[0].bodySprite.setPosition(parts[0].position);
}

void Snake::AddBody(sf::Vector2f position)
{
	SnakePart newPart{ position, parts[1].bodySprite};
	newPart.bodySprite.setPosition(position);
	parts.push_back(newPart);
}

void Snake::Kill()
{
	head.loadFromFile("Textures\\snake_green_32xx.png");
}