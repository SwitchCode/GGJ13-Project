#include "config.hpp"
#include "obstacle.hpp"

Obstacle::Obstacle()
{
}

bool Obstacle::init()
{
    if (!_texture.loadFromFile(IMAGES_PATH"runner/obstacle.png"))
    {
        return false;
    }
    else
    {
        _sprite.setTexture(_texture);
        _pos.x = WINDOW_WIDTH;
        _pos.y = WINDOW_HEIGHT - OBSTACLE_HEIGHT;
        return true;
    }
    _launched = false;
}

int Obstacle::getPosX()
{
    return _pos.x;
}

int Obstacle::getPosY()
{
    return _pos.y;
}

void Obstacle::setPosX(int X)
{
    _pos.x = X;
}

void Obstacle::setPosY(int Y)
{
    _pos.y = Y;
}

void Obstacle::addPosX(int X)
{
    _pos.x += X;
}

void Obstacle::addPosY(int Y)
{
    _pos.y += Y;
}

void Obstacle::launch(int speedX)
{
    _launched = true;
    _speedX = speedX;
}

bool Obstacle::isLaunched()
{
    return _launched;
}

void Obstacle::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;

    if(_launched and _elapsedTime > sf::milliseconds(20))
    {
        if(_pos.x - _speedX > -OBSTACLE_WIDTH)
            _pos.x -= _speedX;
        else
        {
            _launched = false;
            _speedX = 0;
            _pos.x = WINDOW_WIDTH;
        }
        _elapsedTime = sf::milliseconds(0);
    }
    _sprite.setPosition(_pos.x, _pos.y);
}

void Obstacle::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
}
