#include "config.hpp"

#include "heart.hpp"

Heart::Heart() : _currentLife(HEARTS_NUMBER - 1), _currentCombos(0), _isAlive(true)
{
}

Heart::~Heart()
{
}

bool Heart::init(bool retry)
{
    int itemsNumber = std::max(HEARTS_NUMBER, COMBOS_NUMBER);
    _currentLife = HEARTS_NUMBER - 1;
    _currentCombos = 0;
    _isAlive = true;

    if(!retry)
    {
        if(!_hearts.loadFromFile(IMAGES_PATH"rythm/hearts.png"))
            return false;
        else
        {
            for(int i = 0 ; i < COMBOS_NUMBER ; i++)
            {
                _spriteCombos[i].setTexture(_hearts);
                _spriteCombos[i].setTextureRect(sf::IntRect((_spriteCombos[i].getGlobalBounds().width / itemsNumber) * i,
                                                     0,
                                                     _spriteCombos[i].getGlobalBounds().width / itemsNumber,
                                                     _spriteCombos[i].getGlobalBounds().height / 2));
                _spriteCombos[i].setPosition(WINDOW_WIDTH - _spriteCombos[i].getGlobalBounds().width,
                                             WINDOW_HEIGHT - (1.5 * _spriteCombos[i].getGlobalBounds().height));
            }

            for(int i = 0 ; i < HEARTS_NUMBER ; i++)
            {
                _spriteLife[i].setTexture(_hearts);
                _spriteLife[i].setTextureRect(sf::IntRect((_spriteLife[i].getGlobalBounds().width / itemsNumber) * i,
                                                     _spriteLife[i].getGlobalBounds().height / 2,
                                                     _spriteLife[i].getGlobalBounds().width / itemsNumber,
                                                     _spriteLife[i].getGlobalBounds().height / 2));
                _spriteLife[i].setPosition(WINDOW_WIDTH - _spriteLife[i].getGlobalBounds().width,
                                           WINDOW_HEIGHT - (1.5 * _spriteLife[i].getGlobalBounds().height));
            }
        }
    }
    return true;
}

void Heart::update()
{
}

void Heart::draw(sf::RenderWindow &app)
{
    app.draw(_spriteLife[_currentLife]);
    app.draw(_spriteCombos[_currentCombos]);
}

void Heart::beatWave()
{
    hitCombo();
    //_sprite[_currentHeart].setScale(1.2f, 1.2f);
    // do something here if you want
}

void Heart::losePieceOfHeart()
{
    _currentLife--;
    if(_currentLife <= 0)
    {
        _currentLife = 0;
        _isAlive = false;
    }
}

void Heart::breakCombo()
{
    _currentCombos = 0;
}

void Heart::hitCombo()
{
    _currentCombos++;
    if(_currentCombos >= COMBOS_NUMBER)
    {
        _currentCombos = 0;
        _currentLife++;
        if(_currentLife >= HEARTS_NUMBER - 1)
            _currentLife = HEARTS_NUMBER - 1;
    }
}

int Heart::getCurrentHeart()
{
    return _currentLife;
}

bool Heart::isAlive()
{
    return _isAlive;
}

sf::Rect<float> Heart::getRect()
{
    return _spriteCombos[0].getGlobalBounds();
}
