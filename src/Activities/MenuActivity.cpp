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
    gameState.counter++;
    if (gameState.counter == 180) {
        gameState.counter = 0;
        std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>();
        gameState.setCurrentActivity(std::move(fight));
    }
}