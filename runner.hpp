#ifndef RUNNER_HPP
#define RUNNER_HPP

#include "char.hpp"
#include "obstacle.hpp"
#include "background.hpp"

class Runner
{
    private :
        Char _char;
        Obstacle _obstacle;
        Background _background1;
        Background _background2;
        Background _background3;
        Background _background4;
        sf::Texture _texture;
        sf::Sprite _spriteChoc;
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
        bool init(bool retry = false);
        bool verifyCollision(sf::Time elapsedTime);
        bool verifyEffort();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &window);
        int getScore();
};


#endif
