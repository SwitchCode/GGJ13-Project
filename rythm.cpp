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
    _background.setPosition(WINDOW_WIDTH - _background.getGlobalBounds().width, 0);

    if(!_heart.init())
        return false;

    return true;
}

void Rythm::update()
{
    _heart.update();
}

void Rythm::draw(sf::RenderWindow &app)
{
    app.draw(_background);
    _heart.draw(app);
}
