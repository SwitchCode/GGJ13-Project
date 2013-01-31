#include "config.hpp"
#include "char.hpp"

Char::Char(): _currentFrame(0)
{
}

bool Char::init(bool retry)
{
    _pos.x = POS_X;
    _pos.y = WINDOW_HEIGHT - CHAR_HEIGHT;
    _speedY = 0;
    _isJumping = false;
    _currentFrame = 0;

    if(!retry)
    {
        if (!_texture.loadFromFile(IMAGES_PATH"runner/char.png") || !_buffer.loadFromFile(SOUNDS_PATH"step.wav"))
            return false;
        else
        {
            for(int i = 0 ; i < CHAR_FRAME_NUMBER ; i++)
            {
                _spriteRunning[i].setTexture(_texture);
                _spriteRunning[i].setTextureRect(sf::IntRect((_spriteRunning[i].getGlobalBounds().width / 16) * i, 0,
                    _spriteRunning[i].getGlobalBounds().width / 16,
                    _spriteRunning[i].getGlobalBounds().height / 3));
            }
            for(int i = 0 ; i < CHAR_FRAME_NUMBER ; i++)
            {
                _spriteJumping[i].setTexture(_texture);
                _spriteJumping[i].setTextureRect(sf::IntRect((_spriteJumping[i].getGlobalBounds().width / 16) * i, _spriteJumping[i].getGlobalBounds().height / 3,
                    _spriteJumping[i].getGlobalBounds().width / 16,
                    _spriteJumping[i].getGlobalBounds().height / 3));
            }
            for(int i = 0 ; i < 4 ; i++)
            {
                _spriteJumping[i + 16].setTexture(_texture);
                _spriteJumping[i + 16].setTextureRect(sf::IntRect((_spriteJumping[i + 16].getGlobalBounds().width / 16) * i, _spriteJumping[i + 16].getGlobalBounds().height / 3 * 2,
                    _spriteJumping[i + 16].getGlobalBounds().width / 16,
                    _spriteJumping[i + 16].getGlobalBounds().height / 3));
            }

            _stepSound.setBuffer(_buffer);
        }
    }

    return true;
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
    if(_isJumping and _elapsedTime > sf::milliseconds(561 * ACCELERATION /(2*V0)))
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
        if(!_isJumping and _currentFrame >= CHAR_FRAME_NUMBER)
            _currentFrame = 0;
        else if(_isJumping and _currentFrame >= JUMPING_FRAME_NUMBER)
            _currentFrame = JUMPING_FRAME_NUMBER - 1;
        else
            _currentFrame++;

        if(!_isJumping and (_currentFrame == 0 or _currentFrame == 7))
        {
           _stepSound.play();
        }

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
