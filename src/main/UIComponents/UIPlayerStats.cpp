#include "UIComponents/UIPlayerStats.hpp"


UIPlayerStats::UIPlayerStats(GameState &gameState) {
    sf::Vector2u windowSize = gameState.gameWindow->getSize();
    sf::Color statsValueFontColor = sf::Color::Yellow;
    sf::Color statsLabelFontColor = sf::Color::White;
    int numStats = 2;
    sf::Vector2f playerStatsBoxPosition = this->characterStatsBox.getPosition();
    this->statsTextHeight = windowSize.y * 0.025;;

    this->playerName.setFont(gameState.mainFont);
    this->playerName.setString(gameState.player.name);
    this->playerName.setCharacterSize(windowSize.y*0.03);
    this->playerName.setFillColor(sf::Color::White);

    this->playerHealthLabel.setFont(gameState.mainFont);
    this->playerHealthLabel.setString("Health:");
    this->playerHealthLabel.setCharacterSize(statsTextHeight);
    this->playerHealthLabel.setFillColor(statsLabelFontColor);

    this->playerHealthValue.setFont(gameState.mainFont);
    this->playerHealthValue.setString(std::to_string(gameState.player.health));
    this->playerHealthValue.setCharacterSize(statsTextHeight);
    this->playerHealthValue.setFillColor(statsValueFontColor);

    this->playerAttackStrengthLabel.setFont(gameState.mainFont);
    this->playerAttackStrengthLabel.setString("ATK:");
    this->playerAttackStrengthLabel.setCharacterSize(statsTextHeight);
    this->playerAttackStrengthLabel.setFillColor(statsLabelFontColor);

    this->playerAttackStrengthValue.setFont(gameState.mainFont);
    this->playerAttackStrengthValue.setString(std::to_string(gameState.player.attackStrength));
    this->playerAttackStrengthValue.setCharacterSize(statsTextHeight);
    this->playerAttackStrengthValue.setFillColor(statsValueFontColor);

    this->setPosition(0., 0.);
}

void UIPlayerStats::draw(sf::RenderWindow &gameWindow) {
    this->characterStatsBox.draw(gameWindow);
    gameWindow.draw(this->playerName);
    gameWindow.draw(this->playerHealthLabel);
    gameWindow.draw(this->playerHealthValue);
    gameWindow.draw(this->playerAttackStrengthLabel);
    gameWindow.draw(this->playerAttackStrengthValue);
}

sf::Vector2f UIPlayerStats::getPosition() {
    return this->characterStatsBox.getPosition();
}
void UIPlayerStats::setPosition(float x, float y) {
    this->characterStatsBox.setPosition(x, y);

    sf::Vector2f playerStatsBoxPosition = this->characterStatsBox.getPosition();
    sf::FloatRect playerStatsBoxSize = this->characterStatsBox.getSize();
    float statsLabelPosX = playerStatsBoxPosition.x + playerStatsBoxSize.width * 0.1;
    float statsValuePosX = playerStatsBoxPosition.x + playerStatsBoxSize.width * 0.5;
    float statsOffsetY = playerStatsBoxSize.height * 0.25;
    float statsSeparationPaddingY = playerStatsBoxSize.height * 0.05;

    sf::FloatRect playerNameRec = this->playerName.getGlobalBounds();
    this->playerName.setPosition(x + (playerStatsBoxSize.width - playerNameRec.width)/2, y + playerStatsBoxSize.height * 0.1);
    this->playerHealthLabel.setPosition(statsLabelPosX, y + statsOffsetY);
    this->playerHealthValue.setPosition(statsValuePosX, y + statsOffsetY);
    this->playerAttackStrengthLabel.setPosition(statsLabelPosX, y + statsOffsetY + statsTextHeight + statsSeparationPaddingY);
    this->playerAttackStrengthValue.setPosition(statsValuePosX, y + statsOffsetY + statsTextHeight + statsSeparationPaddingY);
}
sf::FloatRect UIPlayerStats::getSize() {
    return this->characterStatsBox.getSize();
}