#include "FightActivity.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

void FightActivity::displayActivity(sf::RenderWindow& window, sf::Texture &background) {
    sf::Vector2u winSize = window.getSize();
    sf::Vector2u imgSize = background.getSize();
    sf::Sprite sprite;
    sprite.setTexture(background);
    /* Tried to scale manually
        int scale = max(winSize.x/imgSize.x, winSize.y/imgSize.y);
        sprite.scale(scale, scale);
    */
    window.draw(sprite);
}