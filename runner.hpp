#ifndef RUNNER_HPP
#define RUNNER_HPP

#include "char.hpp"
#include "obstacle.hpp"

class Runner
{
    private :
        Char _char;
        Obstacle _obstacle;
        sf::Texture _textureObstacle;
        sf::Sprite _spriteObstacle;
        sf::Time _elapsedTime;
        sf::Time _elapsedTimeCollision;
        bool collision;
    public :
        Runner();
        bool init();
        bool verifyCollision(sf::Time elapsedTime);
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &window);
};


#endif
