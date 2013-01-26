#include "config.hpp"
#include "runner.hpp"


Runner::Runner() : _collision(false), _effort(false), _speedChar(5), _delaiObstacle(5000), _score(0)
{
}

bool Runner::init()
{
    if(!_char.init() or !_obstacle.init() or  !_font.loadFromFile(FONTS_PATH"arial.ttf"))
        return false;
    else
    {
        _textScore.setString(toString(_score) + " meters");
        _textScore.setFont(_font);
        _textScore.setColor(sf::Color(0, 0, 0));
        return true;
    }
}

bool Runner::verifyCollision(sf::Time elapsedTime)
{
    _elapsedTimeCollision += elapsedTime;
    sf::Rect<float> obj1(_char.getPosX(), _char.getPosY(), CHAR_WIDTH, CHAR_HEIGHT);
    sf::Rect<float> obj2(_obstacle.getPosX(), _obstacle.getPosY(), CHAR_WIDTH, CHAR_HEIGHT);

    if(_elapsedTimeCollision > sf::milliseconds(1000))
        _collision = false;

    if(AABBvSAABB(obj1, obj2) and !_collision)
    {
        _elapsedTimeCollision = sf::milliseconds(0);
        _collision = true;
        return true;
    }
    else
    {
        return false;
    }

    return AABBvSAABB(obj1, obj2);
}

bool Runner::verifyEffort()
{
    return _effort;
}

void Runner::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _elapsedTime > sf::milliseconds(100))
    {
        if(!_char.getIsJumping())
        {
            _char.jump();
            _effort = true;
        }
        else
            _effort = false;

        _elapsedTime = sf::milliseconds(0);
    }
    else
        _effort = false;

    _elapsedTimeObstacle += elapsedTime;
    if(!_obstacle.isLaunched() and _elapsedTimeObstacle > sf::milliseconds(_delaiObstacle))
    {
        _elapsedTimeObstacle = sf::milliseconds(0);
        _obstacle.launch(_speedChar);
    }

    _totalElapsedTime += elapsedTime;
    if(_totalElapsedTime > sf::seconds(8))
    {
        _delaiObstacle -= 500;
        _speedChar += 2;
        _totalElapsedTime = sf::milliseconds(0);
    }

    _elapsedTimeScore += elapsedTime;
    if(_elapsedTimeScore > sf::milliseconds(10000/_speedChar))
    {
        _score ++;
        _elapsedTimeScore = sf::milliseconds(0);
    }

    _textScore.setString(toString(_score) + " meters");
    _char.update(elapsedTime);
    _obstacle.update(elapsedTime);
}

void Runner::draw(sf::RenderWindow &window)
{
    window.draw(_textScore);
    _char.draw(window);
    _obstacle.draw(window);
}
