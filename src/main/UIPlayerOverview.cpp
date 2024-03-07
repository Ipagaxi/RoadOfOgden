#include "UIPlayerOverview.hpp"

UIPlayerOverview::UIPlayerOverview(GameState &gameState): statsComponent(gameState, gameState.player), playerFrame("monster_landscape_cut/" + gameState.player.picPath, "actor_borders/fight_border.png") {
    sf::Vector2u windowSize = gameState.gameWindow->getSize();

    sf::FloatRect boxRect = this->backgroundBox.getSize();
    this->backgroundBox.setPosition(windowSize.x * 0.01, (windowSize.y-boxRect.height) * 0.5);
    
    float relativeOuterPaddingStatBoxes = 0.05;
    sf::FloatRect statsBoxSize = this->statsComponent.getSize();
    this->statsComponent.setPosition(windowSize.x * 0.08, windowSize.y * 0.35);

    sf::Vector2f statsPos = this->statsComponent.getPosition();
    sf::FloatRect statsSize = this->statsComponent.getSize();
    sf::FloatRect playerFrameRect = this->playerFrame.getSize();
    float playerBoxScale = (windowSize.x*0.22)/playerFrameRect.width;
    this->playerFrame.scale(playerBoxScale, playerBoxScale);
    playerFrameRect = this->playerFrame.getSize();
    this->playerFrame.setPosition(statsPos.x + statsSize.width*0.5 - playerFrameRect.width/2.f, windowSize.y * 0.11);

    sf::Vector2f playerFramePos = this->playerFrame.getPosition();
    this->playerBackgroundTX.loadFromFile(RESOURCE_PATH "actor_landscape_backgrounds/forest.png");
    this->playerBackgroundSP.setTexture(this->playerBackgroundTX);
    sf::FloatRect playerBackgroundRect = this->playerBackgroundSP.getGlobalBounds();
    this->playerBackgroundSP.setOrigin(playerBackgroundRect.width/2.f, playerBackgroundRect.height/2.f);
    this->playerBackgroundSP.setPosition(playerFramePos.x + playerFrameRect.width/2.f, playerFramePos.y + playerFrameRect.height/2.f);
    this->playerBackgroundSP.scale(playerBoxScale, playerBoxScale);
}

void UIPlayerOverview::draw(sf::RenderWindow &gameWindow) {
    this->backgroundBox.draw(gameWindow);
    this->statsComponent.draw(gameWindow);
    gameWindow.draw(this->playerBackgroundSP);
    this->playerFrame.draw(gameWindow);
}