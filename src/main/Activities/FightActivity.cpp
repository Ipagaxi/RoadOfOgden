#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(GameState &gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/fightBG.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    this->colorText.setFont(gameState.mainFont);
    this->colorText.setString("(0, 0, 0)");
    this->colorText.setCharacterSize(gameState.gameWindow->getSize().y*0.05);
    this->colorText.setFillColor(sf::Color::Black);
    sf::FloatRect textRec = this->colorText.getGlobalBounds();
    this->colorText.setOrigin(textRec.width/2, textRec.height/2);
    sf::Vector2u windowSize = gameState.gameWindow->getSize();
    this->colorText.setPosition(windowSize.x/2, windowSize.y*0.8);
}

void FightActivity::runFight(GameState &gameState) {
    this->colorBox.updateClickedPixelColor(gameState, this->pickedColor);
    std::cout << "Blue: " << std::to_string(this->pickedColor.b) << std::endl;
    this->colorText.setString("(" + std::to_string(this->pickedColor.r) +  ", " + std::to_string(this->pickedColor.g) + ", " + std::to_string(this->pickedColor.b) + ")");
}

void FightActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u windowSize = window->getSize();
    sf::Vector2u colorBoxSize = this->colorBox.getSize();
    this->runFight(gameState);
    window->draw(this->backgroundSP);
    this->colorBox.setPosition((windowSize.x - colorBoxSize.x)/2, (windowSize.y - colorBoxSize.y)/2);
    this->colorBox.draw(*gameState.gameWindow);
    window->draw(this->colorText);
}