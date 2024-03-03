#include "Activities/MenuActivity.hpp"

MenuActivity::MenuActivity(GameState &gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/backgroundMenu.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    this->buttonsBackgroundTX.loadFromFile(RESOURCE_PATH "box_backgrounds/menu_border_with_name.png");
    this->buttonsBackgroundSP.setTexture(this->buttonsBackgroundTX);
    //this->buttonsBackgroundSP.setColor(sf::Color(132, 78, 27, 220));

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(gameState.gameWindow->getSize());
    sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(this->backgroundTX.getSize());
    sf::Vector2f backgroundScale = sf::Vector2f(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
    this->backgroundSP.scale(backgroundScale);

    sf::FloatRect buttonsBackgroundRect = this->buttonsBackgroundSP.getGlobalBounds();
    this->buttonsBackgroundSP.setPosition((windowSize.x - buttonsBackgroundRect.width)*0.5, (windowSize.y - buttonsBackgroundRect.height)*0.5);

    sf::FloatRect buttonFightSize = this->buttonFight.getSize();
    this->buttonFight.setPosition((windowSize.x - buttonFightSize.width)*0.5, windowSize.y * 0.65);

    sf::FloatRect buttonExitSize = this->buttonExit.getSize();
    this->buttonExit.setPosition((windowSize.x - buttonExitSize.width)*0.5, windowSize.y * 0.72);
}

void MenuActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;

    window->draw(this->backgroundSP);
    window->draw(this->buttonsBackgroundSP);
    
    this->buttonFight.draw(*gameState.gameWindow);
    this->buttonExit.draw(*gameState.gameWindow);

    if (buttonFight.clickListener(gameState)) {
        std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>(gameState);
        gameState.setCurrentActivity(std::move(fight));
    }

    if (buttonExit.clickListener(gameState)) {
        gameState.backgroundMusic.stop();
        gameState.gameWindow->close();
    }
}