#include "config.hpp"
#include "char.hpp"

Char::Char(): _currentFrame(0)
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
        for(int i = 0 ; i < CHAR_FRAME_NUMBER ; i++)
        {
            _spriteRunning[i].setTexture(_texture);
            _spriteRunning[i].setTextureRect(sf::IntRect((_spriteRunning[i].getGlobalBounds().width / CHAR_FRAME_NUMBER) * i, 0,
                _spriteRunning[i].getGlobalBounds().width /  20 * 16 / CHAR_FRAME_NUMBER,
                _spriteRunning[i].getGlobalBounds().height / 2));
        }
        for(int i = 0 ; i < JUMPING_FRAME_NUMBER ; i++)
        {
            _spriteJumping[i].setTexture(_texture);
            _spriteJumping[i].setTextureRect(sf::IntRect((_spriteJumping[i].getGlobalBounds().width / JUMPING_FRAME_NUMBER) * i, _spriteJumping[i].getGlobalBounds().height / 2,
                _spriteJumping[i].getGlobalBounds().width / JUMPING_FRAME_NUMBER,
                _spriteJumping[i].getGlobalBounds().height / 2));
        }
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
    _currentFrame = 0;
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

    _animationElapsedTime += elapsedTime;
    if(_animationElapsedTime > sf::milliseconds(33))
    {
        if(!_isJumping and _currentFrame >= CHAR_FRAME_NUMBER - 1)
            _currentFrame = 0;
        else if(_isJumping and _currentFrame >= JUMPING_FRAME_NUMBER - 1)
            _currentFrame = 0;
        else
            _currentFrame++;


        _animationElapsedTime = sf::milliseconds(0);
    }
    if(!_isJumping)
        _spriteRunning[_currentFrame].setPosition(_pos.x, _pos.y);
    else
        _spriteJumping[_currentFrame].setPosition(_pos.x, _pos.y);
}

void Char::draw(sf::RenderWindow &window)
{
    if(!_isJumping)
        window.draw(_spriteRunning[_currentFrame]);
    else
        window.draw(_spriteJumping[_currentFrame]);
}
