#include "Activities/FightActivity.hpp"

void FightActivity::displayActivity(sf::RenderWindow& window, sf::Texture &background, sf::Texture &gear) {
    sf::Vector2u winSize = window.getSize();
    sf::Vector2u imgSize = background.getSize();
    sf::Sprite sprite;
    sf::Sprite gearSprite;
    gearSprite.setTexture(gear);
    sprite.setTexture(background);
    /* Tried to scale manually
        int scale = max(winSize.x/imgSize.x, winSize.y/imgSize.y);
        sprite.scale(scale, scale);
    */
    window.draw(sprite);
    window.draw(gearSprite);
}