#include "config.hpp"
#include "runner.hpp"


Runner::Runner() : _collision(false), _effort(false), _speedChar(10), _delaiObstacle(5000), _score(0)
{
}

bool Runner::init(bool retry)
{
    _score = 0;
    _collision = false;
    _effort = false;
    _speedChar = 10;
    _delaiObstacle = 5000;

    if(!retry)
    {
        if(!_char.init()
           or !_obstacle.init()
           or !_font.loadFromFile(FONTS_PATH"arial.ttf")
           or !_background1.init("background/background1.png")
           or !_background2.init("background/background2.png")
           or !_background3.init("background/background3.png")
           or !_background4.init("background/background4.png")
           or !_texture.loadFromFile(IMAGES_PATH"runner/choc.png"))
        {return false;}
        else
        {
            _textScore.setString(toString(_score) + " meters");
            _textScore.setFont(_font);
            _textScore.setColor(sf::Color(0, 0, 0));
            _spriteChoc.setTexture(_texture);
            _background1.setPosY(476);
            _background2.setPosY(200);
            _background3.setPosY(200);
            _background4.setPosY(0);
        }
    }
    else
    {
        _background1.setPosY(476);
        _background2.setPosY(200);
        _background3.setPosY(200);
        _background4.setPosY(0);
        _char.init(retry);
        _obstacle.init(retry);
    }
    return true;
}

bool Runner::verifyCollision(sf::Time elapsedTime)
{
    _elapsedTimeCollision += elapsedTime;
    sf::Rect<float> obj1(_char.getPosX() + 80, _char.getPosY(), CHAR_WIDTH - 160, CHAR_HEIGHT - 90);
    sf::Rect<float> obj2(_obstacle.getPosX() + 30, _obstacle.getPosY() + 20, CHAR_WIDTH - 60, CHAR_HEIGHT - 40);

    if(_elapsedTimeCollision > sf::milliseconds(500))
        _collision = false;

    if(AABBvSAABB(obj1, obj2) and !_collision)
    {
        _elapsedTimeCollision = sf::milliseconds(0);
        _collision = true;
        return true;
    }
    else
    {
        return false;
    }

    return AABBvSAABB(obj1, obj2);
}

bool Runner::verifyEffort()
{
    return _effort;
}

void Runner::update(sf::Time elapsedTime)
{
    _elapsedTime += elapsedTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _elapsedTime > sf::milliseconds(100))
    {
        if(!_char.getIsJumping())
        {
            _char.jump();
            _effort = true;
        }
        else
            _effort = false;

        _elapsedTime = sf::milliseconds(0);
    }
    else
        _effort = false;

    _elapsedTimeObstacle += elapsedTime;
    if(!_obstacle.isLaunched() and _elapsedTimeObstacle > sf::milliseconds(_delaiObstacle))
    {
       if(rand() > 0.35)
       {
            _obstacle.launch(_speedChar);
            _obstacle.changeImage((int)(rand() % 5) + 1);
       }
        _elapsedTimeObstacle = sf::milliseconds(0);
    }

    _totalElapsedTime += elapsedTime;
    if(_totalElapsedTime > sf::seconds(8))
    {
        _delaiObstacle -= 500;
        _speedChar += 1;
        _totalElapsedTime = sf::milliseconds(0);
    }

    _elapsedTimeScore += elapsedTime;
    if(_elapsedTimeScore > sf::milliseconds(2500/_speedChar))
    {
        _score ++;
        _elapsedTimeScore = sf::milliseconds(0);
    }

    if(_collision)
        _spriteChoc.setPosition(_char.getPosX(), _char.getPosY());

    _textScore.setString(toString(_score) + " meters");
    _char.update(elapsedTime);
    _background1.setSpeedX(_speedChar);
    _background2.setSpeedX(_speedChar/2);
    _background3.setSpeedX(_speedChar/3);
    _background4.setSpeedX(_speedChar/5);
    _background1.update(elapsedTime);
    _background2.update(elapsedTime);
    _background3.update(elapsedTime);
    _background4.update(elapsedTime);
    _obstacle.update(elapsedTime);
}

void Runner::draw(sf::RenderWindow &window)
{
    _background4.draw(window);
    _background3.draw(window);
    _background2.draw(window);
    _background1.draw(window);
    _char.draw(window);
    _obstacle.draw(window);
    if(_collision)
        window.draw(_spriteChoc);
    window.draw(_textScore);
}

int Runner::getScore()
{
    return _score;
}
