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
        sf::Time _elapsedTimeObstacle;
        sf::Time _totalElapsedTime;
        sf::Time _elapsedTimeScore;
        sf::Font _font;
        sf::Text _textScore;
        int _score;
        bool _collision;
        bool _effort;
        int _speedChar;
        int _delaiObstacle;
    public :
        Runner();
        bool init();
        bool verifyCollision(sf::Time elapsedTime);
        bool verifyEffort();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &window);
};


#endif
