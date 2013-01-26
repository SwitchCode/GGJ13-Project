#ifndef GAME_HPP
#define GAME_HPP

#include "rythm.hpp"
#include "runner.hpp"

class Game
{
    public:
        Game();
        ~Game();

        static void start();
        static sf::RenderWindow& getWindow();
        const static sf::Event& getCurrentEvent();

    private:
        static bool isExiting();
        static void gameLoop();

        static void updateAll();
        static void drawAll();

        enum GameState { Uninitialized, Paused, Playing, Exiting };

        static GameState _gameState;
        static sf::RenderWindow _mainWindow;
        static sf::Event _currentEvent;
        static sf::Clock _clock;

        static Rythm _rythm;
        static Runner _runner;
};

#endif
