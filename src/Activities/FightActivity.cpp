#include "Activities/FightActivity.hpp"

void FightActivity::displayActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u winSize = window->getSize();
    sf::Vector2u imgSize = gameState.textures.background.getSize();
    sf::Sprite sprite;
    sf::Sprite gearSprite;
    gearSprite.setTexture(gameState.textures.gear);
    sprite.setTexture(gameState.textures.background);
    /* Tried to scale manually
        int scale = max(winSize.x/imgSize.x, winSize.y/imgSize.y);
        sprite.scale(scale, scale);
    */
    window->draw(sprite);
    window->draw(gearSprite);
    gameState.currentActivity = Menu;
}