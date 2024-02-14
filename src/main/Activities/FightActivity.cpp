#include "Activities/FightActivity.hpp"


FightActivity::FightActivity() {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/fightBG.png");
    this->backgroundSP.setTexture(this->backgroundTX);
}

void FightActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u windowSize = window->getSize();
    sf::Vector2u colorBoxSize = this->colorBox.getSize();
    window->draw(this->backgroundSP);
    this->colorBox.setPosition((windowSize.x - colorBoxSize.x)/2, (windowSize.y - colorBoxSize.y)/2);
    this->colorBox.draw(*gameState.gameWindow);
}