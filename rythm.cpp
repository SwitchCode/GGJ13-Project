#include "config.hpp"

#include "game.hpp"
#include "rythm.hpp"

Rythm::Rythm() : _deltaBeat(sf::seconds(1))
{
}

Rythm::~Rythm()
{
    std::for_each(_waves.begin(), _waves.end(), WaveDeallocator());
}

bool Rythm::init()
{
    if(!_backgroundO.loadFromFile(IMAGES_PATH"rythm/background.png"))
        return false;
    _background.setTexture(_backgroundO);
    _background.setPosition(WINDOW_WIDTH - _background.getGlobalBounds().width, 0);

    if(!_heart.init())
        return false;

    if(!_waveO.loadFromFile(IMAGES_PATH"rythm/wave.png"))
        return false;

    return true;
}

void Rythm::update(sf::Time elapsedTime)
{
    generateWaves(elapsedTime);

    for(std::list<Wave*>::iterator it = _waves.begin() ; it != _waves.end() ; ++it)
    {
        if(!(*it)->isAlive())
        {
            delete *it;
            it = _waves.erase(it);
        }
    }

    _elapsedTime += elapsedTime;
    for(std::list<Wave*>::const_iterator it = _waves.begin() ; it != _waves.end() ; ++it)
    {
        (*it)->update(elapsedTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && _elapsedTime > sf::milliseconds(100))
    {
        beatWave();
        _elapsedTime = _elapsedTime.Zero;
    }
    _heart.update();
}

void Rythm::draw(sf::RenderWindow &app)
{
    app.draw(_background);

    for(std::list<Wave*>::const_iterator it = _waves.begin() ; it != _waves.end() ; ++it)
    {
        (*it)->draw(app);
    }
    _heart.draw(app);
}

void Rythm::hurted()
{
    _heart.losePieceOfHeart();
}

void Rythm::generateWaves(sf::Time elapsedTime)
{
    _elapsedTimeBeat += elapsedTime;

    if(_elapsedTimeBeat >= _deltaBeat)
    {
        Wave *wave = new Wave();
        wave->init(_waveO);
        _waves.push_back(wave);

        _elapsedTimeBeat = _elapsedTimeBeat.Zero;
    }
}

void Rythm::beatWave()
{
    bool beat = false;
    for(std::list<Wave*>::const_iterator it = _waves.begin() ; it != _waves.end() ; ++it)
    {
        if(AABBvSAABB((*it)->getRect(), _heart.getRect()))
        {
            beat = true;
            _heart.beatWave();
            (*it)->die();
            break;
        }
    }

    if(!beat)
        _heart.losePieceOfHeart();
}
