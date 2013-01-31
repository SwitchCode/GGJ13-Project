#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

class Obstacle
{
    private:
        sf::Texture _texture1;
        sf::Texture _texture2;
        sf::Texture _texture3;
        sf::Texture _texture4;
        sf::Texture _texture5;
        sf::Sprite _sprite1;
        sf::Sprite _sprite2;
        sf::Sprite _sprite3;
        sf::Sprite _sprite4;
        sf::Sprite _sprite5;

        sf::Sprite _sprite;
        pos _pos;
        bool _launched;
        int _speedX;
        sf::Time _elapsedTime;
    public:
        Obstacle();
        bool init(bool retry = false);
        int getPosX();
        int getPosY();
        void setPosX(int X);
        void setPosY(int Y);
        void addPosX(int X);
        void addPosY(int Y);
        void launch(int speedX);
        void changeImage(int numImage);
        bool isLaunched();
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &window);
};

#endif
