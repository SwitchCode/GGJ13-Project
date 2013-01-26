#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <sstream>
#include <list>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define HEARTS_NUMBER 7
#define CHAR_FRAME_NUMBER 16
#define JUMPING_FRAME_NUMBER 20

#define ACCELERATION 1
#define V0 20
#define POS_X 50
#define CHAR_WIDTH 70
#define CHAR_HEIGHT 110

#define OBSTACLE_WIDTH 50
#define OBSTACLE_HEIGHT 100

#define SCALE 1.f

#define IMAGES_PATH "data/images/"
#define FONTS_PATH "data/fonts/"

#define DELTA_GENERATE_TIME_WAVES sf::seconds(2)
#define DELTA_TIME_WAVES sf::milliseconds(10)

bool AABBvSAABB(sf::Rect<float> rect1, sf::Rect<float> rect2);

struct pos
{
    int x;
    int y;
};

std::string toString(int n);

#endif

