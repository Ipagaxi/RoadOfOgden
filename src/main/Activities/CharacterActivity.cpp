#include "Activities/CharacterActivity.hpp"

CharacterActivity::CharacterActivity(Game &game): Activity(game) {
  this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/backgroundMenu.png");
  this->backgroundSP.setTexture(this->backgroundTX);
}

ActivityEnum CharacterActivity::executeActivity(Game &game) {
  ActivityEnum currentActivity = ActivityEnum::Character;

  sf::RenderWindow *gameWindow = game.renderEngine.gameWindow;
  gameWindow->draw(this->backgroundSP);
  this->exitButton.draw(gameWindow);
  if (this->exitButton.clickListener(gameWindow, game.gameEvents)) {
    currentActivity = ActivityEnum::Menu;
  }
  return currentActivity;
}