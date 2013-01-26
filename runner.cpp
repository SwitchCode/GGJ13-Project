#include "config.hpp"
#include "runner.hpp"


Runner::Runner()
{
}

bool Runner::init()
{
    /*if (!_textureObstacle.loadFromFile(IMAGES_PATH"runner/obstacle.png"))
    {
        return false;
    }
    else
    {
        _spriteObstacle.setTexture(_textureObstacle);
        return true;
    }*/

    if(!_char.init() or !_obstacle.init())
        return false;
    else
        return true;

    _collision = false;
    _effort = false;
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
    if(!_obstacle.isLaunched() and _elapsedTimeObstacle > sf::milliseconds(1000))
    {
        _elapsedTimeObstacle = sf::milliseconds(0);
        _obstacle.launch(25);
    }
    _char.update(elapsedTime);
    _obstacle.update(elapsedTime);
}

void Runner::draw(sf::RenderWindow &window)
{
    _char.draw(window);
    _obstacle.draw(window);
}
