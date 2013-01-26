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
}

void Char::update()
{

}

void Char::draw(sf::RenderWindow &window)
{
    window.draw(_sprite);
}
