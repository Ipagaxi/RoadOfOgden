#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class Textures {
    private:
        sf::Texture background;
        sf::Texture gear;

        sf::Texture getTexture(string textureName);
    public:

        Textures();
};