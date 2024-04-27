#include "GameEngine.h"

GameEngine::GameEngine(int windowWidth, int windowHeight, std::string name, int SnakeSize):
	window(sf::VideoMode(windowWidth, windowHeight), name),
	snake(SnakeSize, windowWidth/2, windowHeight/2),
	apple(32, 32, Apple::red),
	moveDir{sf::Vector2f(1.0, 0)},
	count{0},
	dirChanged{false},
	gameOver{false}
{
	font.loadFromFile("Roboto-Italic.ttf");
	counter.setFont(font);
	counter.setString("Score: 0");
	counter.setCharacterSize(24);
	counter.setFillColor(sf::Color::Cyan);
	counter.setPosition(window.getSize().x - 32*5, window.getSize().y - 80);

	window.init();
}

void GameEngine::checkButtons()
{
	if (!dirChanged)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) && moveDir != sf::Vector2f(0.0, -1.0))
		{
			moveDir = sf::Vector2f(0.0, -1.0); //up
			dirChanged = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) && moveDir != sf::Vector2f(0.0, 1.0))
		{
			moveDir = sf::Vector2f(0.0, 1.0); //down
			dirChanged = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) && moveDir != sf::Vector2f(-1.0, 0.0))
		{
			moveDir = sf::Vector2f(1.0, 0.0); //right
			dirChanged = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) && moveDir != sf::Vector2f(1.0, 0.0))
		{
			moveDir = sf::Vector2f(-1.0, 0.0); //left
			dirChanged = true;
		}
	}
}

bool GameEngine::CheckIfHitWall()
{
	if (snake.parts[0].position.x + moveDir.x * snake.textureSize == 0
		|| snake.parts[0].position.x + moveDir.x * snake.textureSize == window.getSize().x - window.wallSize
		|| snake.parts[0].position.y + moveDir.y * snake.textureSize == 0
		|| snake.parts[0].position.y + moveDir.y * snake.textureSize == window.getSize().y - window.wallSize)
	{
		snake.Kill();
		gameOver = true;
		return true;
	}

	return false;
}

bool GameEngine::CheckIfHitItself()
{
	for (int i = 1; i < snake.parts.size() - 1; i++)
	{
		if (snake.parts[0].position.x + moveDir.x * snake.textureSize == snake.parts[i].position.x
			&& snake.parts[0].position.y + moveDir.y * snake.textureSize == snake.parts[i].position.y)
		{
			gameOver = true;
			snake.Kill();
			return true;
		}
	}

	return false;
}

bool GameEngine::CheckIfHitApple()
{
	if (snake.parts[0].position.x == apple.getPosition().x
		&& snake.parts[0].position.y == apple.getPosition().y)
		return true;

	return false;
}

void GameEngine::updateCounter()
{
	counter.setString("Score: " + std::to_string(++count));
}

void GameEngine::CheckWin()
{
	if (count >= (((window.getSize().x - 2 * window.wallSize) / window.wallSize *
		(window.getSize().y - 2 * window.wallSize)) / window.wallSize))
	{
		//counter.setPosition((window.getSize().x - 2 * window.wallSize) / 2, (window.getSize().y) / 2);
		counter.setCharacterSize(128);
		counter.setOrigin((window.getSize().x + 2 * window.wallSize) / 2, (window.getSize().y) / 2);
		counter.setString("You Won");

		gameOver = true;
	}

}

void GameEngine::Update(sf::Clock& clock)
{
	sf::Vector2f nextPart = snake.parts.back().position;

	if (clock.getElapsedTime().asSeconds() >= 0.17)
	{
		CheckWin();
		CheckIfHitItself();
		CheckIfHitWall();

		if (!gameOver)
		{
			snake.Move(moveDir);
			if (CheckIfHitApple())
			{
				int x = window.wallSize + rand() % (((window.getSize().x - 2 * window.wallSize) / window.wallSize)) * window.wallSize;
				int y = window.wallSize + rand() % (((window.getSize().y - 2 * window.wallSize) / window.wallSize)) * window.wallSize;

				while ([&x, &y, this]()
					{
						for (int i = 0; i < snake.parts.size(); i++)
						{
							if (snake.parts[i].position == sf::Vector2f(x, y))
								return true;
						}

						return false;
					}())
				{
					x = window.wallSize + rand() % (((window.getSize().x - 2 * window.wallSize) / window.wallSize)) * window.wallSize;
					y = window.wallSize + rand() % (((window.getSize().y - 2 * window.wallSize) / window.wallSize)) * window.wallSize;
				}

				apple.changePosition(x, y);
				updateCounter();
				snake.AddBody(nextPart);
			}
			dirChanged = false;
		}
		else
			return;
		clock.restart();
	}
}

void GameEngine::StartGame()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		checkButtons();
		Update(clock);

		window.clear();

		window.drawBackground();
		window.draw(snake);
		window.draw(apple);

		window.sf::RenderWindow::draw(counter);

		window.display();
	}
}