#include "config.hpp"
#include "char.hpp"

Char::Char()
{
}

bool Char::init()
{
    if (!_texture.loadFromFile(IMAGES_PATH"runner/char.png"))
    {
        return false;
    }
    else
    {
        _sprite.setTexture(_texture);
        _pos.x = POS_X;
        _pos.y = WINDOW_HEIGHT - CHAR_HEIGHT;
        return true;
    }

    _speedY = 0;
    _isJumping = false;
}

int Char::getPosX()
{
    return _pos.x;
}

int Char::getPosY()
{
    return _pos.y;
}

bool Char::getIsJumping()
{
    return _isJumping;
}

void Char::setPosX(int X)
{
    _pos.x = X;
}

void Char::setPosY(int Y)
{
    _pos.y = Y;
}

void Char::addPosX(int X)
{
    _pos.x += X;
}

void Char::addPosY(int Y)
{
    _pos.y += Y;
}

void Char::jump()
{
    _isJumping = true;
    _speedY = V0;
}

void Char::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;

    if(_isJumping and _elapsedTime > sf::milliseconds(20))
    {
        _speedY -= ACCELERATION;
        if(_pos.y - _speedY < WINDOW_HEIGHT - CHAR_HEIGHT)
            _pos.y -= _speedY;
        else
        {
            _isJumping = false;
            _speedY = 0;
            _pos.y = WINDOW_HEIGHT - CHAR_HEIGHT;
        }
        _elapsedTime = sf::milliseconds(0);
    }
    _sprite.setPosition(_pos.x, _pos.y);
}

void Char::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
}
