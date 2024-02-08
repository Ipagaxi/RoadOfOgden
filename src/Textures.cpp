#include "Textures.hpp"

sf::Texture Textures::getTexture(string textureName) {
    sf::Texture texture;
    if (!texture.loadFromFile("../../src/ressources/" + textureName)) {
        cout << "Error loading " << textureName << endl;
    }
    return texture;
}

Textures::Textures() {
    Textures::background = getTexture("background.png");
    Textures::gear = getTexture("gear.png");
}