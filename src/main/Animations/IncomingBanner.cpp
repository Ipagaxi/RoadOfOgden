#include "Animations/IncomingBanner.hpp"

void IncomingBanner::init(Game &game) {
    sf::Vector2u windowSize = game.renderEngine.gameWindow->getSize();

    this->banner.setSize(sf::Vector2f(windowSize.x, windowSize.y * 0.2));
    this->banner.setFillColor(sf::Color(40, 40, 40, 210));

    this->bannerText.setFont(game.mainFont);
    this->bannerText.setCharacterSize(game.renderEngine.gameWindow->getSize().y * 0.1);
    this->bannerText.setFillColor(sf::Color::White);
    sf::FloatRect textRec = this->bannerText.getGlobalBounds();
    this->bannerText.setOrigin(textRec.width * 0.5, textRec.height * 0.5);
}

IncomingBanner::IncomingBanner(Game &game) {
    this->init(game);
}

IncomingBanner::IncomingBanner(Game &game, std::string label) {
    this->bannerText.setString(label);
    this->init(game);
}

void IncomingBanner::setNewLabel(std::string newLabel) {
    this->bannerText.setString(newLabel);
    sf::FloatRect textRec = this->bannerText.getGlobalBounds();
    this->bannerText.setOrigin(textRec.width * 0.5, textRec.height * 0.5);
}

bool IncomingBanner::runAnimation(Game &game) {

    int changeTimeMillSec = 1000; // The entire screen time of the banner
    int bannerMovementime = 300; // The time only for movement of the banner => after movement ended banner is still on screen shortly

    float pastTimeRatio = std::min(this->pastMovementTime/static_cast<float>(bannerMovementime), 1.0f);
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(game.renderEngine.gameWindow->getSize());
    sf::FloatRect bannerSize = this->banner.getGlobalBounds();
    sf::Vector2f bannerPos = sf::Vector2f(-windowSize.x + pastTimeRatio * windowSize.x, (windowSize.y - bannerSize.height) * 0.5f);
    this->banner.setPosition(bannerPos.x, bannerPos.y);
    this->bannerText.setPosition(bannerPos.x + bannerSize.width * 0.5, bannerPos.y + bannerSize.height * 0.5);

    this->pastTimeInMillSec += game.gameStatus.elapsedTime.asMilliseconds();
    if (this->pastMovementTime < bannerMovementime) {
        this->pastMovementTime += game.gameStatus.elapsedTime.asMilliseconds();
    }
    if (this->pastTimeInMillSec >= changeTimeMillSec) {
      this->animationStillActive = false;
      bannerPos = sf::Vector2f(-windowSize.x, (windowSize.y - bannerSize.height) * 0.5f);
      this->banner.setPosition(bannerPos.x, bannerPos.y);
      this->bannerText.setPosition(bannerPos.x + bannerSize.width * 0.5, bannerPos.y + bannerSize.height * 0.5);
      this->pastTimeInMillSec = 0;
      this->pastMovementTime = 0;
    }
    return animationStillActive;
}

void IncomingBanner::drawAnimation(sf::RenderWindow* gameWindow) {
    std::cout << "Banner is drawn!" << std::endl;
    gameWindow->draw(this->banner);
    gameWindow->draw(this->bannerText);
}