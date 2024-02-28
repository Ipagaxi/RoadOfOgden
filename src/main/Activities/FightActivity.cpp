#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(GameState &gameState) : playerStatsBox(gameState, gameState.player), enemyStatsBox(gameState, Enemy("Zucchini?!?", 20, 5, {100, 190, 30}, "zucchini_damon.png", "colorPIC_1.png", "borderMetal.png")) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/fightBG.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(gameState.gameWindow->getSize());
    sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(this->backgroundTX.getSize());

    sf::Vector2f backgroundScale = sf::Vector2f(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
    this->backgroundSP.scale(backgroundScale);
    this->colorText.setFont(gameState.mainFont);
    this->colorText.setString("(0, 0, 0)");
    this->colorText.setCharacterSize(gameState.gameWindow->getSize().y*0.05);
    this->colorText.setFillColor(sf::Color::Black);
    sf::FloatRect textRec = this->colorText.getGlobalBounds();
    this->colorText.setOrigin(textRec.width/2, textRec.height/2);
    this->colorText.setPosition(windowSize.x/2, windowSize.y*0.8);
    this->colorBox.scale(0.6, 0.6);

    float relativeOuterPaddingStatBoxes = 0.02;
    this->playerStatsBox.setPosition(windowSize.x * relativeOuterPaddingStatBoxes, (windowSize.y - this->playerStatsBox.getSize().height)/2);
    sf::FloatRect enemyStatsBoxSize = this->enemyStatsBox.getSize();
    this->enemyStatsBox.setPosition(windowSize.x * (1.0 - relativeOuterPaddingStatBoxes) - enemyStatsBoxSize.width, ((windowSize.y - this->playerStatsBox.getSize().height)/2));

    this->colorBox.setColorBox(this->enemy.colorPicPath, this->enemy.colorPicBorderPath);
    sf::FloatRect colorBoxSize = this->colorBox.getSize();
    this->colorBox.setPosition(windowSize.x * 0.6, windowSize.y * 0.35);

    this->enemyPicTX.loadFromFile(RESOURCE_PATH "monster_pics/" + this->enemy.picPath);
    this->enemyPicSP.setTexture(this->enemyPicTX);
    sf::FloatRect enemyPicSize = this->enemyPicSP.getGlobalBounds();
    this->enemyPicSP.setOrigin(enemyPicSize.width/2, 0);
    sf::Vector2f colorBoxPos = this->colorBox.getPosition();
    std::cout << "colorBox Pos x (later): " << colorBoxPos.x << std::endl;
    this->enemyPicSP.setPosition(colorBoxPos.x + colorBoxSize.width*0.5, windowSize.y * 0.01);
    this->enemyPicSP.scale(0.5, 0.5);
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
    sf::FloatRect colorBoxSize = this->colorBox.getSize();
    sf::FloatRect buttonSize = this->exitButton.getSize();
    
    this->exitButton.setPosition(windowSize.x * 0.99 - buttonSize.width, windowSize.x * 0.01);
    this->runFight(gameState);
    window->draw(this->backgroundSP);
    this->playerStatsBox.draw(*window);
    this->enemyStatsBox.draw(*window);

    this->colorBox.draw(*gameState.gameWindow);

    window->draw(this->colorText);
    window->draw(this->enemyPicSP);

    this->exitButton.draw(*gameState.gameWindow);

    if (this->exitButton.clickListener(gameState)) {
        std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>(gameState);
        gameState.setCurrentActivity(std::move(menu));
    }
}