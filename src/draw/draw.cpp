#include <iostream>
#include <SFML/Graphics.hpp>
#include "draw.hpp"

using namespace std;

    sf::Texture draw() {
        sf::Texture texture;
        if (!texture.loadFromFile("../../src/ressources/start_background.png")) {
            cout << "load image" << endl;
        }
        return texture;
    }