#include "config.hpp"

#include "heart.hpp"

Heart::Heart() : _currentHeart(0), _isAlive(true)
{
}

Heart::~Heart()
{
}

bool Heart::init()
{
    if(!_hearts.loadFromFile(IMAGES_PATH"rythm/hearts.png"))
        return false;

    for(int i = 0 ; i < HEARTS_NUMBER ; i++)
    {
        _sprite[i].setTexture(_hearts);
        _sprite[i].setTextureRect(sf::IntRect((_sprite[i].getGlobalBounds().width / HEARTS_NUMBER) * i,
                                             0,
                                             _sprite[i].getGlobalBounds().width / HEARTS_NUMBER,
                                            _sprite[i].getGlobalBounds().height));
    }

    return true;
}

void Heart::update()
{
}

void Heart::draw(sf::RenderWindow &app)
{
    _sprite[_currentHeart].setPosition(WINDOW_WIDTH - _sprite[_currentHeart].getGlobalBounds().width,
                           WINDOW_HEIGHT - (1.5 * _sprite[_currentHeart].getGlobalBounds().height));
    app.draw(_sprite[_currentHeart]);
}

void Heart::beatWave()
{
    //_sprite[_currentHeart].setScale(1.2f, 1.2f);
    // do something here if you want
}

void Heart::losePieceOfHeart()
{
    _currentHeart++;
    if(_currentHeart >= HEARTS_NUMBER - 1)
    {
        _currentHeart = HEARTS_NUMBER - 1;
        _isAlive = false;
    }
}

int Heart::getCurrentHeart()
{
    return _currentHeart;
}

bool Heart::isAlive()
{
    return _isAlive;
}

sf::Rect<float> Heart::getRect()
{
    return _sprite[_currentHeart].getGlobalBounds();
}
