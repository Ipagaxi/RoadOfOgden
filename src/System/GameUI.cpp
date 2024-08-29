#include "GameUI.hpp"

#include "Game.hpp"

GameUI::GameUI() {
  this->backgroundTX.loadFromFile(RESOURCE_PATH + "backgrounds/backgroundMenu.png");
  this->backgroundSP.setTexture(this->backgroundTX);
}

void GameUI::changeBackgroundTexture(std::string filename) {
  this->backgroundTX.loadFromFile(RESOURCE_PATH + "backgrounds/" + filename);
  this->backgroundSP.setTexture(this->backgroundTX);
}

