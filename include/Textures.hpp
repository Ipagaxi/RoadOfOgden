#ifndef TEXTURES
#define TEXTURES

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class Textures {
    private:
        sf::Texture getTexture(string textureName);

    public:
        sf::Texture background;
        sf::Texture gear;
        sf::Texture menuBackground;

        Textures();
};

#endif