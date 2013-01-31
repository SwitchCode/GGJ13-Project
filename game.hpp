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
        static void drawScores();
        static void easterEgg();
        static void splashscreen();

        enum GameState { Uninitialized, Paused, Splashscreen, Playing, Ending, Exiting };

        static GameState _gameState;
        static sf::RenderWindow _mainWindow;
        static sf::Event _currentEvent;
        static sf::Clock _clock;
        static std::string _easterEgg;
        static sf::Time _elapsedEaster;
        static sf::Texture _texture;
        static sf::Sprite _endImg;

        static Rythm _rythm;
        static Runner _runner;
};

#endif
