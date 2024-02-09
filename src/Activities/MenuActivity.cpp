#include "Activities/MenuActivity.hpp"

void MenuActivity::displayActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u winSize = window->getSize();
    sf::Vector2u imgSize = gameState.textures.menuBackground.getSize();
    sf::Sprite sprite;
    sprite.setTexture(gameState.textures.menuBackground);
    /* Tried to scale manually
        int scale = max(winSize.x/imgSize.x, winSize.y/imgSize.y);
        sprite.scale(scale, scale);
    */
    window->draw(sprite);
}