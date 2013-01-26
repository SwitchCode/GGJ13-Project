#ifndef HEART_HPP
#define HEART_HPP

class Heart
{
    public:
        Heart();
        ~Heart();

        bool init();
        void update();
        void draw(sf::RenderWindow &app);

    private:
        sf::Texture _hearts;
        sf::Sprite _sprite[HEARTS_NUMBER];
};

#endif

