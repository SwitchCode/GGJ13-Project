#ifndef RYTHM_HPP
#define RYTHM_HPP

#include "heart.hpp"

class Rythm
{
    public:
        Rythm();
        ~Rythm();

        bool init();
        void update();
        void draw(sf::RenderWindow &app);

    private:
        sf::Texture _backgroundO;
        sf::Sprite _background;

        Heart _heart;
};

#endif
