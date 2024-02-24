#include "UIComponents/UIPlayerStats.hpp"

UIPlayerStats::UIPlayerStats(GameState &gameState) {
    sf::Vector2u windowSize = gameState.gameWindow->getSize();
    float statsTextHeight = windowSize.y * 0.025;
    sf::Color statsValueFontColor = sf::Color::Yellow;
    sf::Color statsLabelFontColor = sf::Color::White;
    int numStats = 2;
    sf::Vector2u playerStatsBoxSize = this->characterStatsBox.getSize();
    sf::Vector2f playerStatsBoxPosition = this->characterStatsBox.getPosition();
    float statsLabelPosX = playerStatsBoxPosition.x + playerStatsBoxSize.x * 0.1;
    float statsValuePosX = playerStatsBoxPosition.x + playerStatsBoxSize.x * 0.5;

    this->characterStatsBox.setPosition(windowSize.x * 0.1, (windowSize.y - playerStatsBoxSize.y)/2);

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
    this->playerAttackStrengthLabel.setString("Attack Strength:");
    this->playerAttackStrengthLabel.setCharacterSize(statsTextHeight);
    this->playerAttackStrengthLabel.setFillColor(statsLabelFontColor);

    this->playerAttackStrengthValue.setFont(gameState.mainFont);
    this->playerAttackStrengthValue.setString(std::to_string(gameState.player.attackStrength));
    this->playerAttackStrengthValue.setCharacterSize(statsTextHeight);
    this->playerAttackStrengthValue.setFillColor(statsValueFontColor);

    sf::FloatRect playerNameRec = this->playerName.getGlobalBounds();
    this->playerName.setPosition(playerStatsBoxPosition.x + (playerStatsBoxSize.x - playerNameRec.width)/2, playerStatsBoxPosition.y + playerStatsBoxSize.y * 0.1);

    sf::FloatRect playerHealthLabelRec = this->playerHealthLabel.getGlobalBounds();
    this->playerHealthLabel.setPosition(statsLabelPosX, playerStatsBoxPosition.y + playerNameRec.height + 2*(playerStatsBoxSize.y * 0.1));

    sf::FloatRect playerHealthValueRec = this->playerHealthValue.getGlobalBounds();
    this->playerHealthValue.setPosition(statsValuePosX, playerStatsBoxPosition.y + playerNameRec.height + 2*(playerStatsBoxSize.y * 0.1));

    sf::FloatRect playerAttackStrengthLabelRec = this->playerAttackStrengthLabel.getGlobalBounds();
    this->playerAttackStrengthLabel.setPosition(statsLabelPosX, playerStatsBoxPosition.y + playerNameRec.height + 2*(playerStatsBoxSize.y * 0.1));

    sf::FloatRect playerAttackStrengthValueRec = this->playerAttackStrengthValue.getGlobalBounds();
    this->playerHealthValue.setPosition(statsValuePosX, playerStatsBoxPosition.y + playerNameRec.height + 2*(playerStatsBoxSize.y * 0.1));
}