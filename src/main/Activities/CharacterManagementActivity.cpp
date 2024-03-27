#include "Activities/CharacterManagementActivity.hpp"

CharacterManagementActivity::CharacterManagementActivity(GameState &gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/backgroundMenu.png");
    this->backgroundSP.setTexture(this->backgroundTX);
}

void CharacterManagementActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    window->draw(this->backgroundSP);
}