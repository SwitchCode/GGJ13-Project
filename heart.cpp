#include "config.hpp"

#include "heart.hpp"

Heart::Heart()
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
    _sprite[/*current*/0].setPosition(WINDOW_WIDTH - _sprite[/*current*/0].getGlobalBounds().width,
                           WINDOW_HEIGHT - (1.5 * _sprite[/*current*/0].getGlobalBounds().height));
    app.draw(_sprite[/*current*/0]);
}
