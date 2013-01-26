#ifndef RUNNER_HPP
#define RUNNER_HPP

#include "char.hpp"

class Runner
{
    private :
        Char _char;
        sf::Texture _textureObstacle;
        sf::Sprite _spriteObstacle;
        sf::Time _elapsedTime;
    public :
        Runner();
        bool init();
        void update(sf::Time elapsedTime);
        bool AABBvSAABB(sf::Rect<float> rect1, sf::Rect<float> rect2);
        void draw(sf::RenderWindow &window);
};


#endif
