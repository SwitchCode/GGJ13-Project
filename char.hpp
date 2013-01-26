#ifndef CHAR_HPP
#define CHAR_HPP

#define POS_X 50
#define CHAR_WIDTH 39
#define CHAR_HEIGHT 54

struct pos
{
    int x;
    int y;
};

class Char
{
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
        pos _pos;
    public:
        Char();
        bool init();
        void update();
        void draw(sf::RenderWindow &window);
};

#endif CHAR_H
