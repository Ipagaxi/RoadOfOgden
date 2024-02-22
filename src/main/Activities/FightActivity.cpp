#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(GameState &gameState) {
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

    this->playerName.setFont(gameState.mainFont);
    this->playerName.setString(gameState.player.name);
    this->playerName.setCharacterSize(windowSize.y*0.03);
    this->playerName.setFillColor(sf::Color::White);

    this->playerHealthLabel.setFont(gameState.mainFont);
    this->playerHealthLabel.setString("Health: ");
    this->playerHealthLabel.setCharacterSize(windowSize.y * 0.025);
    this->playerHealthLabel.setFillColor(sf::Color::White);

    this->playerHealthValue.setFont(gameState.mainFont);
    this->playerHealthValue.setString(std::to_string(gameState.player.health));
    this->playerHealthValue.setCharacterSize(windowSize.y * 0.025);
    this->playerHealthValue.setFillColor(sf::Color::Yellow);


    sf::Vector2u playerStatsBoxSize = this->characterStatsBox.getSize();
    this->characterStatsBox.setPosition(windowSize.x * 0.1, (windowSize.y - playerStatsBoxSize.y)/2);

    sf::Vector2f playerStatsBoxPosition = this->characterStatsBox.getPosition();
    sf::FloatRect playerNameRec = this->playerName.getGlobalBounds();
    this->playerName.setPosition(playerStatsBoxPosition.x + (playerStatsBoxSize.x - playerNameRec.width)/2, playerStatsBoxPosition.y + playerStatsBoxSize.y * 0.1);

    sf::FloatRect playerHealthLabelRec = this->playerHealthLabel.getGlobalBounds();
    this->playerHealthLabel.setPosition(playerStatsBoxPosition.x + playerStatsBoxSize.x * 0.1, playerStatsBoxPosition.y + playerNameRec.height + 2*(playerStatsBoxSize.y * 0.1));

    sf::FloatRect playerHealthValueRec = this->playerHealthValue.getGlobalBounds();
    this->playerHealthValue.setPosition(playerStatsBoxPosition.x + playerStatsBoxSize.x * 0.5, playerStatsBoxPosition.y + playerNameRec.height + 2*(playerStatsBoxSize.y * 0.1));
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
    sf::Vector2u colorBoxSize = this->colorBox.getSize();
    sf::Vector2u buttonSize = this->exitButton.getSize();
    
    this->exitButton.setPosition(windowSize.x * 0.99 - buttonSize.x, windowSize.x * 0.01);
    this->runFight(gameState);
    window->draw(this->backgroundSP);

    this->colorBox.setPosition(windowSize.x * 0.6, (windowSize.y - colorBoxSize.y)/2);
    this->colorBox.draw(*gameState.gameWindow);

    window->draw(this->colorText);

    this->exitButton.draw(*gameState.gameWindow);

    this->characterStatsBox.draw(*gameState.gameWindow);
    window->draw(this->playerName);
    window->draw(this->playerHealthLabel);
    window->draw(this->playerHealthValue);

    if (this->exitButton.clickListener(gameState)) {
        std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>();
        gameState.setCurrentActivity(std::move(menu));
    }
}