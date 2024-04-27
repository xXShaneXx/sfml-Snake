#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include "GameWindow.h"
#include "Snake.h"
#include "GameEngine.h"


#define WINDOW_HIGHT 640 //192 //480 //640 
#define WINDOW_WIDTH 960 //192 //640 //960 

int main()
{
    GameEngine engine(WINDOW_WIDTH, WINDOW_HIGHT, "Snake Game", 3);
    engine.StartGame();

    return 0;
}