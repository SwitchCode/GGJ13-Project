#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

class Obstacle
{
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
        pos _pos;
        bool _launched;
        int _speedX;
        sf::Time _elapsedTime;
    public:
        Obstacle();
        bool init();
        int getPosX();
        int getPosY();
        void setPosX(int X);
        void setPosY(int Y);
        void addPosX(int X);
        void addPosY(int Y);
        void launch(int speedX);
        bool isLaunched();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &window);
};

#endif
