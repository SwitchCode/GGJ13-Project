#ifndef RYTHM_HPP
#define RYTHM_HPP

#include "heart.hpp"

class Rythm
{
    public:
        Rythm();
        ~Rythm();

        bool init();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &app);

    private:
        sf::Texture _backgroundO;
        sf::Sprite _background;
        sf::Time _elapsedTime;

        Heart _heart;
};

#endif
