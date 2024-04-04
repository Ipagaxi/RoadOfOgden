#include "Activities/CharacterManagementActivity.hpp"

CharacterManagementActivity::CharacterManagementActivity(GameState &gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/backgroundMenu.png");
    this->backgroundSP.setTexture(this->backgroundTX);
}

ActivityEnum CharacterManagementActivity::executeActivity(GameState &game) {
  ActivityEnum currentActivity = ActivityEnum::Character;

  sf::RenderWindow *window = game.renderEngine.gameWindow;
  window->draw(this->backgroundSP);
  return currentActivity;
}