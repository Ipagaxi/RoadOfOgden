#include "Activities/FightActivity.hpp"


FightActivity::FightActivity() {
    FightActivity::background.loadFromFile(RESOURCE_PATH "background.png");
    FightActivity::gear.loadFromFile(RESOURCE_PATH "gear_small.png");
}

void FightActivity::displayActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u winSize = window->getSize();
    sf::Vector2u imgSize = FightActivity::background.getSize();
    sf::Sprite backgroundSprite;
    sf::Sprite gearSprite;
    gearSprite.setTexture(FightActivity::gear);
    backgroundSprite.setTexture(FightActivity::background);
    /* Tried to scale manually
        int scale = max(winSize.x/imgSize.x, winSize.y/imgSize.y);
        sprite.scale(scale, scale);
    */
    window->draw(backgroundSprite);
    window->draw(gearSprite);
    gameState.counter++;
    if (gameState.counter == 120) {
        gameState.counter = 0;
        std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>();
        gameState.setCurrentActivity(std::move(menu));
    }
}