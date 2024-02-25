#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(GameState &gameState) : playerStatsBox(gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/fightBG.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    sf::Vector2u windowSize = gameState.gameWindow->getSize();

    this->colorText.setFont(gameState.mainFont);
    this->colorText.setString("(0, 0, 0)");
    this->colorText.setCharacterSize(gameState.gameWindow->getSize().y*0.05);
    this->colorText.setFillColor(sf::Color::Black);
    sf::FloatRect textRec = this->colorText.getGlobalBounds();
    this->colorText.setOrigin(textRec.width/2, textRec.height/2);
    this->colorText.setPosition(windowSize.x/2, windowSize.y*0.8);
    this->colorBox.scale(0.6, 0.6);

    this->playerStatsBox.setPosition(windowSize.x * 0.1, (windowSize.y - this->playerStatsBox.getSize().height)/2);
}

void FightActivity::runFight(GameState &gameState) {
    sf::Vector2f clickedPos;
    if (this->colorBox.clickListener(gameState, clickedPos)) {
        this->pickedColor = this->colorBox.getPixelColor(clickedPos);
        this->colorText.setString("(" + std::to_string(this->pickedColor.r) +  ", " + std::to_string(this->pickedColor.g) + ", " + std::to_string(this->pickedColor.b) + ")");
    }
}

void FightActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u windowSize = window->getSize();
    sf::FloatRect colorBoxSize = this->colorBox.getSize();
    sf::FloatRect buttonSize = this->exitButton.getSize();
    
    this->exitButton.setPosition(windowSize.x * 0.99 - buttonSize.width, windowSize.x * 0.01);
    this->runFight(gameState);
    window->draw(this->backgroundSP);
    this->playerStatsBox.setPosition(windowSize.x * 0.1, (windowSize.y - this->playerStatsBox.getSize().height)/2);
    this->playerStatsBox.draw(*window);

    this->colorBox.setPosition(windowSize.x * 0.6, (windowSize.y - colorBoxSize.height)/2);
    this->colorBox.draw(*gameState.gameWindow);

    window->draw(this->colorText);

    this->exitButton.draw(*gameState.gameWindow);

    if (this->exitButton.clickListener(gameState)) {
        std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>();
        gameState.setCurrentActivity(std::move(menu));
    }
}