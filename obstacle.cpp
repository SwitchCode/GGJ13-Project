#include "config.hpp"
#include "obstacle.hpp"

Obstacle::Obstacle()
{
}

bool Obstacle::init(bool retry)
{
    _pos.x = WINDOW_WIDTH;
    _pos.y = WINDOW_HEIGHT - OBSTACLE_HEIGHT - 20;
    _launched = false;

    if(!retry)
    {
        if (!_texture1.loadFromFile(IMAGES_PATH"runner/barriere.png") ||
            !_texture2.loadFromFile(IMAGES_PATH"runner/haie.png") ||
            !_texture3.loadFromFile(IMAGES_PATH"runner/rocher.png") ||
            !_texture4.loadFromFile(IMAGES_PATH"runner/poubelle.png") ||
            !_texture5.loadFromFile(IMAGES_PATH"runner/bouche-incendie.png"))
        {
            return false;
        }
        else
        {
            _sprite1.setTexture(_texture1);
            _sprite2.setTexture(_texture2);
            _sprite3.setTexture(_texture3);
            _sprite4.setTexture(_texture4);
            _sprite5.setTexture(_texture5);
            _sprite = _sprite1;
        }
    }

    return true;
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

void Obstacle::changeImage(int numImage)
{
    if(numImage == 1)
        _sprite = _sprite1;
    else if(numImage == 2)
        _sprite = _sprite2;
    else if(numImage == 3)
        _sprite = _sprite3;
    else if(numImage == 4)
        _sprite = _sprite4;
    else
        _sprite = _sprite5;
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
