#ifndef TEXTURES
#define TEXTURES

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Sprites {
    private:
        sf::Sprite getSprite(std::string textureName);

    public:
        sf::Sprite background;
        sf::Sprite gear;
        sf::Sprite menuBackground;

        Sprites();
};

#endif