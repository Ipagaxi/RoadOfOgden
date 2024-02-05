#include <iostream>
#include "draw.hpp"

using namespace std;

    void draw(sf::RenderWindow& window) {
        sf::Texture texture;
        if (!texture.loadFromFile("../../src/ressources/start_background.png")) {
            cout << "load image" << endl;
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);
        window.draw(sprite);
    }