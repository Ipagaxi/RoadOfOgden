#include "Activities/FightActivity.hpp"


FightActivity::FightActivity() {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/fightBG.png");
    this->gearTX.loadFromFile(RESOURCE_PATH "deco/gear_small.png");

    this->backgroundSP.setTexture(this->backgroundTX);
    this->gearSP.setTexture(this->gearTX);
}

void FightActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    window->draw(this->backgroundSP);
    window->draw(this->gearSP);
    gameState.counter++;
    if (gameState.counter == 120) {
        gameState.counter = 0;
        std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>();
        gameState.setCurrentActivity(std::move(menu));
    }
}