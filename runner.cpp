#include "config.hpp"
#include "runner.hpp"

Runner::Runner()
{
}

bool Runner::init()
{
    if(!_char.init())
        return false;
    else
        return true;
}

void Runner::update()
{

}

void Runner::draw(sf::RenderWindow &window)
{
    _char.draw(window);
}
