#include "config.hpp"

#include "game.hpp"
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

void Rythm::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && _elapsedTime > sf::milliseconds(100))
    {
        _heart.losePieceOfHeart(); // just a test
        // check here if there is a wave
        _elapsedTime = sf::milliseconds(0);
    }
    _heart.update();
}

void Rythm::draw(sf::RenderWindow &app)
{
    app.draw(_background);
    _heart.draw(app);
}
