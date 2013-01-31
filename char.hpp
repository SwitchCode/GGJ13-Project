#ifndef CHAR_HPP
#define CHAR_HPP

class Char
{
    private:
        sf::Texture _texture;
        sf::Sprite _spriteRunning[CHAR_FRAME_NUMBER];
        sf::Sprite _spriteJumping[JUMPING_FRAME_NUMBER];
        sf::SoundBuffer _buffer;
        sf::Sound _stepSound;
        int _currentFrame;
        pos _pos;
        int _speedY;
        bool _isJumping;
        sf::Time _elapsedTime;
        sf::Time _animationElapsedTime;

    public:
        Char();
        bool init(bool retry = false);
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

#endif
