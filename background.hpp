#ifndef BACKGROUND_H
#define BACKGROUND_H

    class Background
    {
        private:
            sf::Texture _texture;
            sf::Sprite _sprite1;
            sf::Sprite _sprite2;
            pos _pos1;
            pos _pos2;
            int _speedX;
            sf::Time _elapsedTime;
        public:
            Background();
            bool init(std::string backgroundPath, bool retry = false);
            int getPosX();
            int getPosY();
            void setPosY(int Y);
            void setSpeedX(int speedX);
            void update(sf::Time elapsedTime);
            void draw(sf::RenderWindow &window);
    };

#endif
