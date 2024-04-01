#include "Activities/CharacterManagementActivity.hpp"

CharacterManagementActivity::CharacterManagementActivity(GameState &gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/backgroundMenu.png");
    this->backgroundSP.setTexture(this->backgroundTX);
}

void CharacterManagementActivity::executeActivity(GameState &game) {
    sf::RenderWindow *window = game.gameWindow;
    window->draw(this->backgroundSP);
}