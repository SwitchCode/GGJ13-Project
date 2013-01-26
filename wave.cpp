#include "config.hpp"

#include "wave.hpp"

Wave::Wave() : _isAlive(true), _isMissed(false)
{
}

Wave::~Wave()
{
}

bool Wave::init(sf::Texture &texture)
{
    _sprite.setTexture(texture);
    _sprite.setPosition(WINDOW_WIDTH - _sprite.getGlobalBounds().width, - _sprite.getGlobalBounds().height);
}

void Wave::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;
    if(_elapsedTime > sf::milliseconds(10))
    {
        _sprite.move(0, 1);
        if(_sprite.getPosition().y > WINDOW_HEIGHT)
        {
            _isMissed = true;
        }
        _elapsedTime = _elapsedTime.Zero;
    }
}

void Wave::draw(sf::RenderWindow &app)
{
    app.draw(_sprite);
}

void Wave::die()
{
    _isAlive = false;
}

bool Wave::isAlive()
{
    return _isAlive;
}

bool Wave::isMissed()
{
    return _isMissed;
}

sf::Rect<float> Wave::getRect()
{
    return _sprite.getGlobalBounds();
}
