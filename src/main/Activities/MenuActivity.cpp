#include "Activities/MenuActivity.hpp"

MenuActivity::MenuActivity(GameState &gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/menuBG.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(gameState.gameWindow->getSize());
    sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(this->backgroundTX.getSize());
    sf::Vector2f backgroundScale = sf::Vector2f(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
    this->backgroundSP.scale(backgroundScale);
}

void MenuActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u windowSize = window->getSize();
    sf::FloatRect buttonSize = this->button.getSize();

    window->draw(this->backgroundSP);

    this->button.setPosition((windowSize.x - buttonSize.width)/2, (windowSize.y - buttonSize.height)/2);
    this->button.draw(*gameState.gameWindow);

    if (button.clickListener(gameState)) {
        std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>(gameState);
        gameState.setCurrentActivity(std::move(fight));
    }
}