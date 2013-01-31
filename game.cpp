#include "config.hpp"

#include "rythm.hpp"
#include "runner.hpp"
#include "game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::start()
{
    if(_gameState != Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Heart of Jump");

    _gameState = Game::Splashscreen;

    splashscreen();

    _gameState = Game::Playing;

    _mainWindow.setVerticalSyncEnabled(true);

    if (!_texture.loadFromFile(IMAGES_PATH"splash.png"))
        _gameState = Game::Exiting;

    _endImg.setTexture(_texture);
    _endImg.setPosition(0, 0);

    if(!_rythm.init())
        _gameState = Game::Exiting;
    else if(!_runner.init())
        _gameState = Game::Exiting;

    while(!isExiting())
    {
        gameLoop();
    }

    _mainWindow.close();
}

bool Game::isExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}

void Game::gameLoop()
{
    _mainWindow.pollEvent(_currentEvent);
    switch(_gameState)
    {
        case Game::Playing:
            _mainWindow.clear(sf::Color(255, 255, 255));

            updateAll();
            drawAll();

            _mainWindow.display();

            if(_rythm.isTheEnd())
                _gameState = Game::Ending;
            if(_currentEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                _gameState = Game::Exiting;
        break;
        case Game::Ending:
            _mainWindow.clear(sf::Color(0, 0, 0));

            drawScores();

            _elapsedEaster += _clock.restart();
            if(_elapsedEaster >= sf::milliseconds(500) && sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){_easterEgg += "1";}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){_easterEgg += "2";}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){_easterEgg += "3";}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){_easterEgg += "4";}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){_easterEgg += "5" ;}
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){_easterEgg += "6";}
                _elapsedEaster = _elapsedEaster.Zero;
            }

            while(_easterEgg.length() > 10)
            {
                _easterEgg = _easterEgg.substr(1, 10);
            }

            if(_easterEgg == "1122343456")
            {
                _mainWindow.clear(sf::Color(0, 0, 0));
                easterEgg();
            }

            if(_currentEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                _gameState = Game::Exiting;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                 _gameState = Game::Playing;
                 _runner.init(true);
                 _rythm.init(true);
            }

            _mainWindow.display();
        break;
    }
}

void Game::updateAll()
{
    sf::Time elapsed = _clock.restart();

    _rythm.update(elapsed);
    _runner.update(elapsed);
    if(_runner.verifyCollision(elapsed))
        _rythm.hurted();
    if(_runner.verifyEffort())
        _rythm.accelerate();
    else
        _rythm.decelerate(elapsed);
}

void Game::drawAll()
{
    _runner.draw(_mainWindow);
    _rythm.draw(_mainWindow);
}

void Game::drawScores()
{
    sf::Font font;
    sf::Text text, textScores;

    if(!font.loadFromFile(FONTS_PATH"arial.ttf"))
        exit(EXIT_FAILURE);

    text.setFont(font);
    textScores.setFont(font);
    text.setString("GAME OVER");
    textScores.setString("You ran over " + toString(_runner.getScore()) + "m. (R to restart)");
    text.setColor(sf::Color(0, 0, 0));
    textScores.setColor(sf::Color(0, 0, 0));
    text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - text.getGlobalBounds().height);
    textScores.setPosition(WINDOW_WIDTH / 2 - textScores.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 + textScores.getGlobalBounds().height);

    _mainWindow.draw(_endImg);
    _mainWindow.draw(text);
    _mainWindow.draw(textScores);
}

void Game::splashscreen()
{
    sf::Texture background;
    sf::Sprite bgSprite;

    if(!background.loadFromFile(IMAGES_PATH"splashscreen.png"))
        return exit(EXIT_FAILURE);

    bgSprite.setTexture(background);
    bool pass = true;
    while(pass)
    {
        _mainWindow.clear(sf::Color(255, 255, 255));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            pass = false;

        _mainWindow.draw(bgSprite);

        _mainWindow.display();
    }
}

void Game::easterEgg()
{
    sf::Font font;
    sf::Text text;

    if(!font.loadFromFile(FONTS_PATH"arial.ttf"))
        exit(EXIT_FAILURE);

    text.setFont(font);
    text.setString("\\o/");
    text.setCharacterSize(200);
    text.setColor(sf::Color(0, 0, 0));
    text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - text.getGlobalBounds().height / 2);

    _mainWindow.draw(text);
}

sf::RenderWindow& Game::getWindow()
{
    return _mainWindow;
}

const sf::Event& Game::getCurrentEvent()
{
    return _currentEvent;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
sf::Event Game::_currentEvent;
sf::Clock Game::_clock;
std::string Game::_easterEgg;
sf::Time Game::_elapsedEaster;

Rythm Game::_rythm;
Runner Game::_runner;
sf::Texture Game::_texture;
sf::Sprite Game::_endImg;
