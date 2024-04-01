#include "Activities/MenuActivity.hpp"

MenuActivity::MenuActivity(GameState &gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/backgroundMenu.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    this->backgroundMusic.openFromFile(RESOURCE_PATH "music/menu_background_music.wav");
    this->backgroundMusic.setLoop(true);
    this->backgroundMusic.play();

    this->buttonsBackgroundTX.loadFromFile(RESOURCE_PATH "box_backgrounds/menu_border_with_name.png");
    this->buttonsBackgroundSP.setTexture(this->buttonsBackgroundTX);
    //this->buttonsBackgroundSP.setColor(sf::Color(132, 78, 27, 220));

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(gameState.gameWindow->getSize());
    sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(this->backgroundTX.getSize());
    sf::Vector2f backgroundScale = sf::Vector2f(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
    this->backgroundSP.scale(backgroundScale);

    sf::FloatRect buttonsBackgroundRect = this->buttonsBackgroundSP.getGlobalBounds();
    sf::Vector2f buttonsBackgroundPos = sf::Vector2f((windowSize.x - buttonsBackgroundRect.width)*0.5, (windowSize.y - buttonsBackgroundRect.height)*0.5);
    this->buttonsBackgroundSP.setPosition(buttonsBackgroundPos.x, buttonsBackgroundPos.y);

    sf::FloatRect buttonSize = this->buttonFight.getSize();
    this->buttonFight.setPosition(buttonsBackgroundPos.x + (buttonsBackgroundRect.width - buttonSize.width)*0.5, buttonsBackgroundPos.y + buttonsBackgroundRect.height * 0.6);

    this->buttonCharacter.setPosition(buttonsBackgroundPos.x + (buttonsBackgroundRect.width - buttonSize.width)*0.5, buttonsBackgroundPos.y + buttonsBackgroundRect.height * 0.68);

    this->buttonExit.setPosition(buttonsBackgroundPos.x + (buttonsBackgroundRect.width - buttonSize.width)*0.5, buttonsBackgroundPos.y + buttonsBackgroundRect.height * 0.76);
}

MenuActivity::~MenuActivity() {
}

void MenuActivity::executeActivity(GameState &game) {
  sf::RenderWindow* gameWindow = game.renderEngine.gameWindow;

  gameWindow->draw(this->backgroundSP);
  gameWindow->draw(this->buttonsBackgroundSP);

  this->buttonFight.draw(gameWindow);
  this->buttonCharacter.draw(gameWindow);
  this->buttonExit.draw(gameWindow);

  if (buttonFight.clickListener(gameWindow, game.gameEvents)) {
      this->backgroundMusic.stop();
      //std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>(gameState);
      //gameState.setCurrentActivity(std::move(fight));
  }

  if (buttonCharacter.clickListener(gameWindow, game.gameEvents)) {
      this->backgroundMusic.stop();
      //std::unique_ptr<CharacterManagementActivity> charActivity = std::make_unique<CharacterManagementActivity>(gameState);
      //gameState.setCurrentActivity(std::move(charActivity));
  }

  if (buttonExit.clickListener(gameWindow, game.gameEvents)) {
      //gameState.backgroundMusic.stop();
      this->backgroundMusic.stop();
      gameWindow->close();
  }
}