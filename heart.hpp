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

        void losePieceOfHeart();
        int getCurrentHeart();
        bool isAlive();

    private:
        sf::Texture _hearts;
        sf::Sprite _sprite[HEARTS_NUMBER];
        int _currentHeart;
        bool _isAlive;
};

#endif

