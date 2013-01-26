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

bool Runner::AABBvSAABB(sf::Rect<float> rect1, sf::Rect<float> rect2)
{
   return !((rect2.left >= rect1.left + rect1.width)
	|| (rect2.left + rect2.width <= rect1.left)
	|| (rect2.top >= rect1.top + rect1.height)
	|| (rect2.top + rect2.height <= rect1.top));
}

void Runner::draw(sf::RenderWindow &window)
{
    _char.draw(window);
}
