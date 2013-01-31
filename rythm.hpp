#ifndef RYTHM_HPP
#define RYTHM_HPP

#include "heart.hpp"
#include "wave.hpp"

class Rythm
{
    public:
        Rythm();
        ~Rythm();

        bool init(bool retry = false);
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &app);
        void hurted();
        void accelerate();
        void decelerate(sf::Time elapsedTime);

        void createWave();
        void beatWave();
        void generateWaves(sf::Time elapsedTime);

        bool isTheEnd();

    private:
        sf::Texture _backgroundO, _waveO, _lineO;
        sf::Sprite _background, _lineSprite;
        sf::Time _elapsedTime, _deltaBeat, _elapsedTimeBeat, _elapsedTimeAccelerate, _deltaTimeWaves, _elapsedTimeWaves;

        bool _isTheEnd;
        int _totalWaves;
        sf::SoundBuffer _buffer1;
        sf::SoundBuffer _buffer2;
        sf::Sound _heart1;
        sf::Sound _heart2;
        bool _firstHeart;

        Heart _heart;
        std::list<Wave*> _waves;
        bool _security;

        struct WaveDeallocator
        {
            void operator()(const Wave* p) const
            {
                delete p;
            }
        };
};

#endif
