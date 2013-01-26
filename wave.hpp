#ifndef WAVE_HPP
#define WAVE_HPP

class Wave
{
    public:
        Wave();
        ~Wave();

        bool init(sf::Texture &texture);
        void update(sf::Time elapsedTime);
        void draw(sf::RenderWindow &app);

        void die();

        bool isAlive();
        bool isMissed();
        sf::Rect<float> getRect();

    private:
        sf::Sprite _sprite;
        sf::Time _elapsedTime;
        bool _isAlive, _isMissed;
};

#endif


