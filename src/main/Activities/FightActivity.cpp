#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(GameState &gameState) : playerStatsBox(gameState, gameState.player), enemyStatsBox(gameState, Enemy("Zucchini?!?", 20, 5, {100, 190, 30}, "zucchini_demon_quer.png", "colorPIC_0.png", "borderMetal.png")) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/fightBG.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    this->enemy = Enemy("Zucchini?!?", 20, 5, {100, 190, 30}, "zucchini_demon_quer.png", "colorPIC_0.png", "borderMetal.png");

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

    this->lastDamage.setFont(gameState.mainFont);
    this->lastDamage.setString("0");
    this->lastDamage.setCharacterSize(gameState.gameWindow->getSize().y*0.05);
    this->lastDamage.setFillColor(sf::Color::Yellow);

    float relativeOuterPaddingStatBoxes = 0.02;
    this->playerStatsBox.setPosition(windowSize.x * relativeOuterPaddingStatBoxes, (windowSize.y - this->playerStatsBox.getSize().height)/2);
    sf::FloatRect enemyStatsBoxSize = this->enemyStatsBox.getSize();
    this->enemyStatsBox.setPosition(windowSize.x * (1.0 - relativeOuterPaddingStatBoxes) - enemyStatsBoxSize.width, ((windowSize.y - this->playerStatsBox.getSize().height)/2));

    this->colorBox.setColorBox(this->enemy.colorPicPath, this->enemy.colorPicBorderPath);
    sf::FloatRect colorBoxSize = this->colorBox.getSize();
    this->colorBox.setPosition(windowSize.x * 0.6, windowSize.y * 0.35);

    this->enemyPicTX.loadFromFile(RESOURCE_PATH "monster_landscape_cut/" + this->enemy.picPath);
    this->enemyPicSP.setTexture(this->enemyPicTX);
    sf::FloatRect enemyPicSize = this->enemyPicSP.getGlobalBounds();
    this->enemyPicSP.setOrigin(enemyPicSize.width/2, 0);
    sf::Vector2f colorBoxPos = this->colorBox.getPosition();
    this->enemyPicSP.setPosition(colorBoxPos.x + colorBoxSize.width*0.5, windowSize.y * 0.1);
    this->enemyPicSP.scale(0.5, 0.5);
}

void FightActivity::runFight(GameState &gameState) {
    sf::Vector2f clickedPos;
    if (this->colorBox.clickListener(gameState, clickedPos)) {
        sf::Color pickedColor = this->colorBox.getPixelColor(clickedPos);
        this->colorText.setString("(" + std::to_string(pickedColor.r) +  ", " + std::to_string(pickedColor.g) + ", " + std::to_string(pickedColor.b) + ")");
        float attackMultiplier = this->calculateAttackMult(pickedColor.r, pickedColor.g, pickedColor.b);
        std::cout << "Attack Multiplier: " << std::to_string(attackMultiplier) << std::endl;
        int damage = gameState.player.attackStrength * attackMultiplier;
        std::cout << "Damage: " << damage << std::endl;
        this->lastDamage.setString(std::to_string(damage));
        this->enemy.health = std::max(this->enemy.health - damage, 0);
        this->enemyStatsBox.actorHealthValue.setString(std::to_string(std::max(this->enemy.health - damage, 0)));
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
    window->draw(this->lastDamage);

    if (this->exitButton.clickListener(gameState)) {
        std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>(gameState);
        gameState.setCurrentActivity(std::move(menu));
    }
}

float FightActivity::calculateSingleSummand(int pickedRGBComponent, int defenseRGBComponent) {
    int attackDefenseDiff = pickedRGBComponent - defenseRGBComponent;
    std::cout << "Attack defense difference: " << std::to_string(attackDefenseDiff) << std::endl;
    float mappedDiff = (attackDefenseDiff + 255) / 510.0;
    std::cout << "Mapped difference: " << std::to_string(mappedDiff) << std::endl;
    // The following function is to limit the the effect of the single rgb component to a third.
    float mappedToOneThird = (2.f/3) * (mappedDiff*mappedDiff) + (1.f/3) * mappedDiff;
    std::cout << "Mapped to a third: " << std::to_string(mappedToOneThird) << std::endl;
    return mappedToOneThird;

}

float FightActivity::calculateAttackMult(int pickedRed, int pickedGreen, int pickedBlue) {
    float redSummand = this->calculateSingleSummand(pickedRed, this->enemy.defense.red);
    float greenSummand = this->calculateSingleSummand(pickedGreen, this->enemy.defense.green);
    float blueSummand = this->calculateSingleSummand(pickedBlue, this->enemy.defense.blue);
    return (redSummand + greenSummand + blueSummand) * (2.f/3);
}