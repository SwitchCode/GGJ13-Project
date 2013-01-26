#include "config.hpp"

#include "rythm.hpp"
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

    _mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GGJ13-Project");

    _gameState = Game::Playing;

    _mainWindow.setVerticalSyncEnabled(true);

    if(!_rythm.init())
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
        _mainWindow.clear();

        updateAll();
        drawAll();

        _mainWindow.display();

        if(_currentEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            _gameState = Game::Exiting;
        }
        break;
    }
}

void Game::updateAll()
{
    _rythm.update();
}

void Game::drawAll()
{
    _rythm.draw(_mainWindow);
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

Rythm Game::_rythm;
