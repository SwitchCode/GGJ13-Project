#include "config.hpp"
#include "game.hpp"

int main(int argc, char *argv[])
{
    Game::start();

    return EXIT_SUCCESS;
}

std::string toString(int n)
{
    std::ostringstream oss;
    oss << n;

    return oss.str();
}
