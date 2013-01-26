#include "config.hpp"

#include "wave.hpp"

Wave::Wave() : _isAlive(true)
{
}

Wave::~Wave()
{
}

bool Wave::init(sf::Texture &texture)
{
    _sprite.setTexture(texture);
    _sprite.setPosition(WINDOW_WIDTH - _sprite.getGlobalBounds().width, 0);
}

void Wave::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;
    if(_elapsedTime > sf::milliseconds(10))
    {
        _sprite.move(0, 1);
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

sf::Rect<float> Wave::getRect()
{
    return _sprite.getGlobalBounds();
}
