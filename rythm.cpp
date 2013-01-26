#include "config.hpp"

#include "game.hpp"
#include "rythm.hpp"

Rythm::Rythm() : _deltaBeat(DELTA_GENERATE_TIME_WAVES), _deltaTimeWaves(DELTA_TIME_WAVES)
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
        if(!(*it)->isAlive() || (*it)->isMissed())
        {
            if((*it)->isMissed())
            {
                hurted();
                _heart.breakCombo();
            }

            delete *it;
            it = _waves.erase(it);
        }
    }

    _elapsedTime += elapsedTime;
    for(std::list<Wave*>::const_iterator it = _waves.begin() ; it != _waves.end() ; ++it)
    {
        (*it)->update(elapsedTime, _deltaTimeWaves);
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

void Rythm::accelerate()
{
    sf::Time deltaTimeWaves = DELTA_TIME_WAVES;
    if(_deltaTimeWaves.asMilliseconds() > deltaTimeWaves.asMilliseconds() / 4)
        _deltaTimeWaves = sf::milliseconds(_deltaTimeWaves.asMilliseconds() / 2);
}

void Rythm::decelerate(sf::Time elapsedTime)
{
    _elapsedTimeWaves += elapsedTime;

    if(_deltaTimeWaves < DELTA_TIME_WAVES && _elapsedTimeWaves > sf::seconds(10))
    {
        _deltaTimeWaves = sf::milliseconds(_deltaTimeWaves.asMilliseconds() * 2);
        if(_deltaTimeWaves > DELTA_TIME_WAVES)
            _deltaTimeWaves = DELTA_TIME_WAVES;
        _elapsedTimeWaves = _elapsedTimeWaves.Zero;
    }
}

void Rythm::generateWaves(sf::Time elapsedTime)
{
    _elapsedTimeBeat += elapsedTime;

    if(!_waves.empty())
    {
        if(_waves.back()->getPosition().y > _waves.back()->getRect().height)
        {
            Wave *wave = new Wave();
            wave->init(_waveO);
            _waves.push_back(wave);

            _elapsedTimeBeat = _elapsedTimeBeat.Zero;
        }
    }
    else
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
        else
        {
            _heart.breakCombo();
        }
    }

    if(!beat)
        _heart.losePieceOfHeart();
}
