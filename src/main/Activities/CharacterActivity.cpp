#include "Activities/CharacterActivity.hpp"

CharacterActivity::CharacterActivity(Game &game): Activity(game) {
  this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/backgroundMenu.png");
  this->backgroundSP.setTexture(this->backgroundTX);
}

ActivityEnum CharacterActivity::executeActivity(Game &game) {
  ActivityEnum currentActivity = ActivityEnum::Character;

  sf::RenderWindow *window = game.renderEngine.gameWindow;
  window->draw(this->backgroundSP);
  return currentActivity;
}