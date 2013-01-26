#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <list>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define HEARTS_NUMBER 7

#define ACCELERATION 1
#define V0 20
#define POS_X 50
#define CHAR_WIDTH 70
#define CHAR_HEIGHT 110

#define OBSTACLE_WIDTH 100
#define OBSTACLE_HEIGHT 100

#define SCALE 1.f

#define IMAGES_PATH "data/images/"

bool AABBvSAABB(sf::Rect<float> rect1, sf::Rect<float> rect2);

struct pos
{
    int x;
    int y;
};


#endif

