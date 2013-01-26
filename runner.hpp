#ifndef RUNNER_HPP
#define RUNNER_HPP

#include "char.hpp"

class Runner
{
    private :
        Char _char;
    public :
        Runner();
        bool init();
        void update();
        void draw(sf::RenderWindow &window);
};


#endif
