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

    if(!_char.init())
        return false;
    else
        return true;
}

void Runner::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _elapsedTime > sf::milliseconds(100))
    {
        if(!_char.getIsJumping())
            _char.jump();

        _elapsedTime = sf::milliseconds(0);
    }
    _char.update(elapsedTime);
}

void Runner::draw(sf::RenderWindow &window)
{
    _char.draw(window);
}
