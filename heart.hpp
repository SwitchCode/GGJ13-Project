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
        void breakCombo();
        void hitCombo();
        void beatWave();
        int getCurrentHeart();
        sf::Rect<float> getRect();
        bool isAlive();

    private:
        sf::Texture _hearts;
        sf::Sprite _spriteBase, _spriteLife[HEARTS_NUMBER], _spriteCombos[COMBOS_NUMBER];
        int _currentLife, _currentCombos;
        bool _isAlive;
};

#endif

