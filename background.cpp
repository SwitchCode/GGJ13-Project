#include "config.hpp"
#include "background.hpp"

Background::Background()
{
}

bool Background::init(std::string backgroundPath, bool retry)
{
    if(!retry)
    {
        if (!_texture.loadFromFile(IMAGES_PATH + backgroundPath))
        {
            return false;
        }
        else
        {
            _sprite1.setTexture(_texture);
            _sprite2.setTexture(_texture);
            _sprite1.setPosition(0, 0);
            _sprite2.setPosition(_sprite2.getGlobalBounds().width, 0);
        }
    }
    else
    {
        _sprite1.setPosition(0, 0);
        _sprite2.setPosition(_sprite2.getGlobalBounds().width, 0);
    }

    return true;
}

void Background::setPosY(int Y)
{
    _sprite1.setPosition(_sprite1.getPosition().x, Y);
    _sprite2.setPosition(_sprite2.getPosition().x, Y);
}

void Background::setSpeedX(int speedX)
{
    _speedX  = speedX;
}

void Background::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;

    if(_elapsedTime > sf::milliseconds(20))
    {
        _sprite1.move(-_speedX, 0);
        _sprite2.move(-_speedX, 0);

        if(_sprite1.getPosition().x + _sprite1.getGlobalBounds().width <= 0)
            _sprite1.setPosition(_sprite2.getPosition().x + _sprite2.getGlobalBounds().width, _sprite1.getPosition().y);
        if(_sprite2.getPosition().x + _sprite2.getGlobalBounds().width <= 0)
            _sprite2.setPosition(_sprite1.getPosition().x + _sprite1.getGlobalBounds().width, _sprite2.getPosition().y);

        _elapsedTime = _elapsedTime.Zero;
    }
}

void Background::draw(sf::RenderWindow &window)
{
    window.draw(_sprite1);
    window.draw(_sprite2);
}
