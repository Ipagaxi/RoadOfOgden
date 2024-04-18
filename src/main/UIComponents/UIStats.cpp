#include "UIComponents/UIStats.hpp"


UIStats::UIStats(Game &game, Actor actor) {
    sf::Vector2u windowSize = game.renderEngine.gameWindow->getSize();
    sf::Color statsValueFontColor = sf::Color::Yellow;
    sf::Color statsLabelFontColor = sf::Color::White;
    int numStats = 2;
    sf::Vector2f actorStatsBoxPosition = this->actorStatsBox.getPosition();
    this->statsTextHeight = windowSize.y * 0.015;

    float scale = (windowSize.y * 0.4) / this->actorStatsBox.getSize().height;
    this->actorStatsBox.scale(scale, scale);

    sf::FloatRect actorStatsBoxSize = this->actorStatsBox.getSize();
    this->actorStatsBox.setBackgroundMargin(actorStatsBoxSize.width * 0.1, actorStatsBoxSize.height * 0.04);

    this->actorName.setFont(game.mainFont);
    this->actorName.setString(actor.name);
    this->actorName.setCharacterSize(windowSize.y*0.02);
    this->actorName.setFillColor(sf::Color::White);

    this->actorHealthLabel.setFont(game.mainFont);
    this->actorHealthLabel.setString("Health:");
    this->actorHealthLabel.setCharacterSize(statsTextHeight);
    this->actorHealthLabel.setFillColor(statsLabelFontColor);

    this->actorHealthValue.setFont(game.mainFont);
    this->actorHealthValue.setString(std::to_string(actor.health));
    this->actorHealthValue.setCharacterSize(statsTextHeight);
    this->actorHealthValue.setFillColor(statsValueFontColor);

    this->actorAttackStrengthLabel.setFont(game.mainFont);
    this->actorAttackStrengthLabel.setString("ATK:");
    this->actorAttackStrengthLabel.setCharacterSize(statsTextHeight);
    this->actorAttackStrengthLabel.setFillColor(statsLabelFontColor);

    this->actorAttackStrengthValue.setFont(game.mainFont);
    this->actorAttackStrengthValue.setString(std::to_string(actor.attackStrength));
    this->actorAttackStrengthValue.setCharacterSize(statsTextHeight);
    this->actorAttackStrengthValue.setFillColor(statsValueFontColor);

    this->actorRGBDefenseLabel.setFont(game.mainFont);
    this->actorRGBDefenseLabel.setString("DEF:");
    this->actorRGBDefenseLabel.setCharacterSize(statsTextHeight);
    this->actorRGBDefenseLabel.setFillColor(statsLabelFontColor);

    this->actorRGBDefenseValues.setFont(game.mainFont);
    this->actorRGBDefenseValues.setString("(" + std::to_string(actor.defense.red) + ", " + std::to_string(actor.defense.green) + ", " + std::to_string(actor.defense.blue) + ")");
    this->actorRGBDefenseValues.setCharacterSize(statsTextHeight);
    this->actorRGBDefenseValues.setFillColor(statsValueFontColor);

    this->setPosition(0., 0.);
}

void UIStats::setActor(Actor actor) {
  this->actorName.setString(actor.name);
  this->actorHealthValue.setString(std::to_string(actor.health));
  this->actorAttackStrengthValue.setString(std::to_string(actor.attackStrength));
  this->actorRGBDefenseValues.setString("(" + std::to_string(actor.defense.red) + ", " + std::to_string(actor.defense.green) + ", " + std::to_string(actor.defense.blue) + ")");
}

void UIStats::draw(sf::RenderWindow* gameWindow) {
    this->actorStatsBox.draw(gameWindow);
    gameWindow->draw(this->actorName);
    gameWindow->draw(this->actorHealthLabel);
    gameWindow->draw(this->actorHealthValue);
    gameWindow->draw(this->actorAttackStrengthLabel);
    gameWindow->draw(this->actorAttackStrengthValue);
    gameWindow->draw(this->actorRGBDefenseLabel);
    gameWindow->draw(this->actorRGBDefenseValues);
}

sf::Vector2f UIStats::getPosition() {
    return this->actorStatsBox.getPosition();
}
void UIStats::setPosition(float x, float y) {
    this->actorStatsBox.setPosition(x, y);

    sf::Vector2f actorStatsBoxPosition = this->actorStatsBox.getPosition();
    sf::FloatRect actorStatsBoxSize = this->actorStatsBox.getSize();
    float statsLabelPosX = actorStatsBoxPosition.x + actorStatsBoxSize.width * 0.2;
    float statsValuePosX = actorStatsBoxPosition.x + actorStatsBoxSize.width * 0.45;
    float statsOffsetY = actorStatsBoxSize.height * 0.3;
    float statsSeparationPaddingY = actorStatsBoxSize.height * 0.05;

    sf::FloatRect actorNameRec = this->actorName.getGlobalBounds();
    this->actorName.setPosition(x + (actorStatsBoxSize.width - actorNameRec.width)/2, y + actorStatsBoxSize.height * 0.15);
    this->actorHealthLabel.setPosition(statsLabelPosX, y + statsOffsetY);
    this->actorHealthValue.setPosition(statsValuePosX, y + statsOffsetY);
    this->actorAttackStrengthLabel.setPosition(statsLabelPosX, y + statsOffsetY + statsTextHeight + statsSeparationPaddingY);
    this->actorAttackStrengthValue.setPosition(statsValuePosX, y + statsOffsetY + statsTextHeight + statsSeparationPaddingY);
    this->actorRGBDefenseLabel.setPosition(statsLabelPosX, y + statsOffsetY + (statsTextHeight + statsSeparationPaddingY)*2);
    this->actorRGBDefenseValues.setPosition(statsValuePosX, y + statsOffsetY + (statsTextHeight + statsSeparationPaddingY)*2);
}
sf::FloatRect UIStats::getSize() {
    return this->actorStatsBox.getSize();
}

void UIStats::updateHealth(int value) {
    this->actorHealthValue.setString(std::to_string(value));
}
