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

        void beatWave();

    private:
        sf::Texture _backgroundO, _waveO;
        sf::Sprite _background;
        sf::Time _elapsedTime;

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
