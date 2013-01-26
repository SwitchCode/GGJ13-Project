#ifndef CHAR_HPP
#define CHAR_HPP


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
        int _speedY;
        bool _isJumping;
        sf::Time _elapsedTime;

    public:
        Char();
        bool init();
        int getPosX();
        int getPosY();
        bool getIsJumping();
        void setPosX(int X);
        void setPosY(int Y);
        void addPosX(int X);
        void addPosY(int Y);
        void jump();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &window);
};

#endif CHAR_H
