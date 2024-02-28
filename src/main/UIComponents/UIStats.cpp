#include "UIComponents/UIStats.hpp"


UIStats::UIStats(GameState &gameState, Actor actor) {
    sf::Vector2u windowSize = gameState.gameWindow->getSize();
    sf::Color statsValueFontColor = sf::Color::Yellow;
    sf::Color statsLabelFontColor = sf::Color::White;
    int numStats = 2;
    sf::Vector2f actorStatsBoxPosition = this->actorStatsBox.getPosition();
    this->statsTextHeight = windowSize.y * 0.025;;

    this->actorName.setFont(gameState.mainFont);
    this->actorName.setString(actor.name);
    this->actorName.setCharacterSize(windowSize.y*0.03);
    this->actorName.setFillColor(sf::Color::White);

    this->actorHealthLabel.setFont(gameState.mainFont);
    this->actorHealthLabel.setString("Health:");
    this->actorHealthLabel.setCharacterSize(statsTextHeight);
    this->actorHealthLabel.setFillColor(statsLabelFontColor);

    this->actorHealthValue.setFont(gameState.mainFont);
    this->actorHealthValue.setString(std::to_string(actor.health));
    this->actorHealthValue.setCharacterSize(statsTextHeight);
    this->actorHealthValue.setFillColor(statsValueFontColor);

    this->actorAttackStrengthLabel.setFont(gameState.mainFont);
    this->actorAttackStrengthLabel.setString("ATK:");
    this->actorAttackStrengthLabel.setCharacterSize(statsTextHeight);
    this->actorAttackStrengthLabel.setFillColor(statsLabelFontColor);

    this->actorAttackStrengthValue.setFont(gameState.mainFont);
    this->actorAttackStrengthValue.setString(std::to_string(actor.attackStrength));
    this->actorAttackStrengthValue.setCharacterSize(statsTextHeight);
    this->actorAttackStrengthValue.setFillColor(statsValueFontColor);

    this->setPosition(0., 0.);
}

void UIStats::draw(sf::RenderWindow &gameWindow) {
    this->actorStatsBox.draw(gameWindow);
    gameWindow.draw(this->actorName);
    gameWindow.draw(this->actorHealthLabel);
    gameWindow.draw(this->actorHealthValue);
    gameWindow.draw(this->actorAttackStrengthLabel);
    gameWindow.draw(this->actorAttackStrengthValue);
}

sf::Vector2f UIStats::getPosition() {
    return this->actorStatsBox.getPosition();
}
void UIStats::setPosition(float x, float y) {
    this->actorStatsBox.setPosition(x, y);

    sf::Vector2f actorStatsBoxPosition = this->actorStatsBox.getPosition();
    sf::FloatRect actorStatsBoxSize = this->actorStatsBox.getSize();
    float statsLabelPosX = actorStatsBoxPosition.x + actorStatsBoxSize.width * 0.1;
    float statsValuePosX = actorStatsBoxPosition.x + actorStatsBoxSize.width * 0.5;
    float statsOffsetY = actorStatsBoxSize.height * 0.25;
    float statsSeparationPaddingY = actorStatsBoxSize.height * 0.05;

    sf::FloatRect actorNameRec = this->actorName.getGlobalBounds();
    this->actorName.setPosition(x + (actorStatsBoxSize.width - actorNameRec.width)/2, y + actorStatsBoxSize.height * 0.1);
    this->actorHealthLabel.setPosition(statsLabelPosX, y + statsOffsetY);
    this->actorHealthValue.setPosition(statsValuePosX, y + statsOffsetY);
    this->actorAttackStrengthLabel.setPosition(statsLabelPosX, y + statsOffsetY + statsTextHeight + statsSeparationPaddingY);
    this->actorAttackStrengthValue.setPosition(statsValuePosX, y + statsOffsetY + statsTextHeight + statsSeparationPaddingY);
}
sf::FloatRect UIStats::getSize() {
    return this->actorStatsBox.getSize();
}