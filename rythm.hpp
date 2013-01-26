#ifndef RYTHM_HPP
#define RYTHM_HPP

#include "heart.hpp"
#include "wave.hpp"

class Rythm
{
    public:
        Rythm();
        ~Rythm();

        bool init();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &app);
        void hurted();
        void accelerate();
        void decelerate(sf::Time elapsedTime);

        void beatWave();
        void generateWaves(sf::Time elapsedTime);

    private:
        sf::Texture _backgroundO, _waveO;
        sf::Sprite _background;
        sf::Time _elapsedTime, _deltaBeat, _elapsedTimeBeat, _elapsedTimeAccelerate, _deltaTimeWaves, _elapsedTimeWaves;

        Heart _heart;
        std::list<Wave*> _waves;

        struct WaveDeallocator
        {
            void operator()(const Wave* p) const
            {
                delete p;
            }
        };
};

#endif
