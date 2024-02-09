#include "Sprites.hpp"

sf::Sprite Sprites::getSprite(std::string textureName) {
    sf::Texture texture;
    if (!texture.loadFromFile("../../src/ressources/" + textureName)) {
        std::cout << "Error loading " << textureName << std::endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    return sprite;
}

Sprites::Sprites() {
    Sprites::background = getSprite("background.png");
    Sprites::gear = getSprite("gear.png");
    Sprites::menuBackground = getSprite("menu_background.png");
}