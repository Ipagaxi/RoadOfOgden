#include "Animations/IncomingBanner.hpp"

void IncomingBanner::init(GameState &gameState) {
    sf::Vector2u windowSize = gameState.gameWindow->getSize();

    this->banner.setSize(sf::Vector2f(windowSize.x, windowSize.y * 0.2));
    this->banner.setFillColor(sf::Color(40, 40, 40, 210));

    this->bannerText.setFont(gameState.mainFont);
    this->bannerText.setCharacterSize(gameState.gameWindow->getSize().y*0.1);
    this->bannerText.setFillColor(sf::Color::White);
    sf::FloatRect textRec = this->bannerText.getGlobalBounds();
    this->bannerText.setOrigin(textRec.width * 0.5, textRec.height * 0.5);
}

IncomingBanner::IncomingBanner(GameState &gameState) {
    this->init(gameState);
}

IncomingBanner::IncomingBanner(GameState &gameState, std::string label) {
    this->bannerText.setString(label);
    this->init(gameState);
}

void IncomingBanner::setNewLabel(std::string newLabel) {
    this->bannerText.setString(newLabel);
    sf::FloatRect textRec = this->bannerText.getGlobalBounds();
    this->bannerText.setOrigin(textRec.width * 0.5, textRec.height * 0.5);
}

void IncomingBanner::updateAnimation(GameState &gameState, bool &animationRuns) {
    int changeTimeMillSec = 1000;
    int bannerMovementime = 300;
    static int pastTimeInMillSec = 0;
    static int pastMovementTime = 0;
    float pastTimeRatio = std::min(pastMovementTime/static_cast<float>(bannerMovementime), 1.0f);
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(gameState.gameWindow->getSize());
    sf::FloatRect bannerSize = this->banner.getGlobalBounds();
    sf::Vector2f bannerPos = sf::Vector2f(-windowSize.x + pastTimeRatio * windowSize.x, (windowSize.y - bannerSize.height) * 0.5f);
    this->banner.setPosition(bannerPos.x, bannerPos.y);
    this->bannerText.setPosition(bannerPos.x + bannerSize.width * 0.5, bannerPos.y + bannerSize.height * 0.5);

    pastTimeInMillSec += gameState.elapsedTime.asMilliseconds();
    if (pastMovementTime < bannerMovementime) {
        pastMovementTime += gameState.elapsedTime.asMilliseconds();
    }
    if (pastTimeInMillSec >= changeTimeMillSec) {
        animationRuns = false;
        bannerPos = sf::Vector2f(-windowSize.x, (windowSize.y - bannerSize.height) * 0.5f);
        this->banner.setPosition(bannerPos.x, bannerPos.y);
        this->bannerText.setPosition(bannerPos.x + bannerSize.width * 0.5, bannerPos.y + bannerSize.height * 0.5);
        pastTimeInMillSec = 0;
        pastMovementTime = 0;
    }
}

void IncomingBanner::drawAnimation(sf::RenderWindow &gameWindow) {
    gameWindow.draw(this->banner);
    gameWindow.draw(this->bannerText);
}