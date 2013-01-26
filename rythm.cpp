#include "config.hpp"

#include "rythm.hpp"

Rythm::Rythm()
{
}

Rythm::~Rythm()
{
}

bool Rythm::init()
{
    if(!_backgroundO.loadFromFile(IMAGES_PATH"rythm/background.png"))
        return false;
    _background.setTexture(_backgroundO);
    _background.setPosition(WINDOW_WIDTH - _background.getLocalBounds().width, 0);

    return true;
}

void Rythm::update()
{
}

void Rythm::draw(sf::RenderWindow &app)
{
    app.draw(_background);
}
