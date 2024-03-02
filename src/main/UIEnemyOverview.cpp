#include "UIEnemyOverview.hpp"

UIEnemyOverview::UIEnemyOverview(GameState &gameState, Enemy enemy): statsComponent(gameState, enemy), creature(enemy) {
    sf::Vector2u windowSize = gameState.gameWindow->getSize();
    float relativeOuterPaddingStatBoxes = 0.02;
    sf::FloatRect statsBoxSize = this->statsComponent.getSize();
    this->statsComponent.setPosition(windowSize.x * (1.0 - relativeOuterPaddingStatBoxes) - statsBoxSize.width, ((windowSize.y - this->statsComponent.getSize().height)/2));

    std::cout << "Set Color Box" << std::endl;
    this->colorPicker.setColorBox(this->creature.colorPicPath, this->creature.colorPicBorderPath);
    this->colorPicker.setPosition(windowSize.x * 0.6, windowSize.y * 0.35);
    this->colorPicker.scale(0.6, 0.6);

    std::cout << "Enemy Pic Path: " << this->creature.picPath << std::endl;
    this->creatureTX.loadFromFile(RESOURCE_PATH "monster_landscape_cut/" + this->creature.picPath);
    this->creatureSP.setTexture(this->creatureTX);
    sf::FloatRect creaturePicSize = this->creatureSP.getGlobalBounds();
    this->creatureSP.setOrigin(creaturePicSize.width/2, 0);
    sf::Vector2f colorBoxPos = this->colorPicker.getPosition();
    sf::FloatRect colorBoxSize = this->colorPicker.getSize();
    this->creatureSP.setPosition(colorBoxPos.x + colorBoxSize.width*0.5, windowSize.y * 0.1);
    this->creatureSP.scale(0.5, 0.5);
}

void UIEnemyOverview::draw(sf::RenderWindow &gameWindow) {
    this->statsComponent.draw(gameWindow);
    this->colorPicker.draw(gameWindow);
    gameWindow.draw(this->creatureSP);
}

void UIEnemyOverview::changeHealth(int value) {
    int newHealth = std::max(this->creature.health - value, 0);
    this->creature.health = newHealth;
    this->statsComponent.updateHealth(newHealth);
}