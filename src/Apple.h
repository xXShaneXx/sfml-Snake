#pragma once
#include <SFML/Graphics.hpp>
#include "GameWindow.h"

class GameWindow;

class Apple
{
    sf::Texture appleTexture;
    sf::Sprite appleSprite;

    int x;
    int y;

public:
    enum Applecolor
    {
        red,
        green
    };

    Apple(int xx, int yy, Applecolor color);

    sf::Vector2f getPosition();

    void changePosition(int xx, int yy);

    friend void GameWindow::draw(const Apple& apple);
};