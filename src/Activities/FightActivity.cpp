#include "FightActivity.hpp";
#include <iostream>

void FightActivity::displayActivity(sf::RenderWindow& window) {
    sf::Texture texture;
    if (!texture.loadFromFile("../../src/ressources/start_background.png")) {
        cout << "load image" << endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    window.draw(sprite);
}