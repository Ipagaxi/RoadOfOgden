#include "UIObjects/UIPlayerOverview.hpp"

UIPlayerOverview::UIPlayerOverview(): statsComponent(Game::getInstance().player), player(Game::getInstance().player), playerFrame("monster_landscape_cut/" + Game::getInstance().player.picPath, "actor_borders/fight_border.png") {
    Game game = Game::getInstance();
    sf::Vector2u windowSize = game.gameWindow.getSize();
    sf::FloatRect boxRect = this->backgroundBox.getSize();
    this->backgroundBox.setPosition((windowSize.x * 0.49) - boxRect.width, windowSize.y * 0.1);
    
    float relativeOuterPaddingStatBoxes = 0.05;
    sf::FloatRect statsBoxSize = this->statsComponent.getSize();
    this->statsComponent.setPosition(windowSize.x * 0.08, windowSize.y * 0.35);

    sf::Vector2f statsPos = this->statsComponent.getPosition();
    sf::FloatRect statsSize = this->statsComponent.getSize();
    sf::FloatRect playerFrameRect = this->playerFrame.getSize();
    float playerBoxScale = (windowSize.x*0.22)/playerFrameRect.width;
    this->playerFrame.scale(playerBoxScale, playerBoxScale);
    playerFrameRect = this->playerFrame.getSize();
    this->playerFrame.setPosition(statsPos.x + statsSize.width*0.5 - playerFrameRect.width/2.f, windowSize.y * 0.14);

    sf::Vector2f playerFramePos = this->playerFrame.getPosition();
    this->playerBackgroundTX.loadFromFile(RESOURCE_PATH "actor_landscape_backgrounds/forest.png");
    this->playerBackgroundSP.setTexture(this->playerBackgroundTX);
    sf::FloatRect playerBackgroundRect = this->playerBackgroundSP.getGlobalBounds();
    this->playerBackgroundSP.setOrigin(playerBackgroundRect.width/2.f, playerBackgroundRect.height/2.f);
    this->playerBackgroundSP.setPosition(playerFramePos.x + playerFrameRect.width/2.f, playerFramePos.y + playerFrameRect.height/2.f);
    this->playerBackgroundSP.scale(playerBoxScale, playerBoxScale);
}

void UIPlayerOverview::changeHealth(int value) {
    int newHealth = std::max(this->player.health - value, 0);
    this->player.health = newHealth;
    this->statsComponent.updateHealth(newHealth);
}

void UIPlayerOverview::draw() {
    Game game = Game::getInstance();
    this->backgroundBox.draw();
    this->statsComponent.draw();
    game.gameWindow.draw(this->playerBackgroundSP);
    this->playerFrame.draw();
}