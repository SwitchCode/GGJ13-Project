#include "config.hpp"

#include "game.hpp"
#include "rythm.hpp"

Rythm::Rythm() : _deltaBeat(DELTA_GENERATE_TIME_WAVES), _deltaTimeWaves(DELTA_TIME_WAVES), _isTheEnd(false), _totalWaves(0)
{
}

Rythm::~Rythm()
{
    std::for_each(_waves.begin(), _waves.end(), WaveDeallocator());
}

bool Rythm::init(bool retry)
{
    _deltaBeat = DELTA_GENERATE_TIME_WAVES;
    _deltaTimeWaves = DELTA_TIME_WAVES;
    _isTheEnd = false;
    _totalWaves = 0;
    _security = false;
    _firstHeart = true;

    if(!retry)
    {
        if(!_backgroundO.loadFromFile(IMAGES_PATH"rythm/background.png") ||
           !_buffer1.loadFromFile(SOUNDS_PATH"beat1.wav") ||
           !_buffer2.loadFromFile(SOUNDS_PATH"beat2.wav"))
            return false;

        _background.setTexture(_backgroundO);
        _background.setPosition(WINDOW_WIDTH - _background.getGlobalBounds().width, 0);
        _heart1.setBuffer(_buffer1);
        _heart2.setBuffer(_buffer2);

        if(!_lineO.loadFromFile(IMAGES_PATH"rythm/line.png"))
            return false;
        _lineSprite.setTexture(_lineO);
        _lineSprite.setPosition(WINDOW_WIDTH - _lineSprite.getGlobalBounds().width, 0);

        if(!_heart.init())
            return false;

        if(!_waveO.loadFromFile(IMAGES_PATH"rythm/wave.png"))
            return false;
    }
    else
    {
        _heart.init(true);
        std::for_each(_waves.begin(), _waves.end(), WaveDeallocator());
        for(std::list<Wave*>::iterator it = _waves.begin() ; it != _waves.end() ; ++it)
        {
            it = _waves.erase(it);
        }
        _waves.clear();
    }

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
                hurted();

            delete *it;
            it = _waves.erase(it);
        }
    }

    _elapsedTime += elapsedTime;
    for(std::list<Wave*>::const_iterator it = _waves.begin() ; it != _waves.end() ; ++it)
    {
        (*it)->update(elapsedTime, _deltaTimeWaves);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && _elapsedTime > sf::milliseconds(100) && !_security)
    {
        beatWave();
        _elapsedTime = _elapsedTime.Zero;
        _security = true;
    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        _security = false;

    _heart.update();

    if(!_heart.isAlive())
    {
        _isTheEnd = true;
    }
}

void Rythm::draw(sf::RenderWindow &app)
{
    app.draw(_background);
    for(int i = 0 ; i < WINDOW_HEIGHT ; i++)
    {
        bool draw = true;
        for(std::list<Wave*>::const_iterator it = _waves.begin() ; it != _waves.end() ; ++it)
        {
            if(AABBvSAABB((*it)->getRect(),
                                sf::Rect<float>(WINDOW_WIDTH - _lineSprite.getGlobalBounds().width,
                                         i,
                                         _lineSprite.getGlobalBounds().width,
                                         _lineSprite.getGlobalBounds().height)))
            {
                draw = false;
            }
        }

        if(draw)
        {
            _lineSprite.setPosition(WINDOW_WIDTH - _lineSprite.getGlobalBounds().width, i);
            app.draw(_lineSprite);
        }
    }

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
        if(_waves.back()->getPosition().y > _waves.back()->getRect().height && _totalWaves % 2 == 0)
        {
            createWave();
            _elapsedTimeBeat = _elapsedTimeBeat.Zero;
        }
        else if(_waves.back()->getPosition().y > _waves.back()->getRect().height * 2 && _totalWaves % 2 == 1)
        {
            createWave();
            _elapsedTimeBeat = _elapsedTimeBeat.Zero;
        }
    }
    else
    {
        createWave();
        _elapsedTimeBeat = _elapsedTimeBeat.Zero;
    }
}

void Rythm::createWave()
{
    Wave *wave = new Wave();
    wave->init(_waveO);
    _waves.push_back(wave);
    _totalWaves++;
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
            if(_firstHeart)
            {
                _heart1.play();
                _firstHeart = false;
            }
            else
            {
                 _heart2.play();
                _firstHeart = true;
            }

            break;
        }
    }

    if(!beat)
        _heart.losePieceOfHeart();
}

bool Rythm::isTheEnd()
{
    return _isTheEnd;
}
