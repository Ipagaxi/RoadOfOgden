#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(GameState &gameState) : playerStatsBox(gameState, gameState.player), enemyStatsBox(gameState, Enemy("Zucchini?!?", 20, 5, {100, 190, 30}, "zucchini_demon_quer.png", "colorPIC_0.png", "borderMetal.png")) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/background_fight.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    this->enemy = Enemy("Zucchini?!?", 20, 5, {100, 190, 30}, "zucchini_demon_quer.png", "colorPIC_0.png", "borderMetal.png");
    //enemyStatsBox = UIStats(gameState, this->initEnemy());

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

    std::cout << "Set Color Box" << std::endl;
    this->colorBox.setColorBox(this->enemy.colorPicPath, this->enemy.colorPicBorderPath);
    sf::FloatRect colorBoxSize = this->colorBox.getSize();
    this->colorBox.setPosition(windowSize.x * 0.6, windowSize.y * 0.35);

    std::cout << "Enemy Pic Path: " << this->enemy.picPath << std::endl;
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
        this->pickedColor = this->colorBox.getPixelColor(clickedPos);
        this->colorText.setString("(" + std::to_string(pickedColor.r) +  ", " + std::to_string(pickedColor.g) + ", " + std::to_string(pickedColor.b) + ")");
        float attackMultiplier = this->calculateAttackMult();
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

Enemy FightActivity::initEnemy() {
    std::cout << "Init random enemy" << std::endl;
    std::vector<std::string> enemyNames = {"Zucchini?!?", "Assel", "Hamster", "Mantis Warrior", "Flesh-Fungus"};
    Enemy randomEnemy;

    std::srand(std::time(nullptr));
    int randomNum = std::rand() % NUM_ENEMY;


    switch (randomNum) {
        case 0:
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 5) + 8;
            randomEnemy.health = (std::rand() % 12) + 10;
            randomEnemy.defense = {std::rand() % 150, (std::rand() % 50) + 120, std::rand() % 100};
            randomEnemy.picPath = "zucchini_demon_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        case 1:
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 3) + 3;
            randomEnemy.health = (std::rand() % 4) + 20;
            randomEnemy.defense = {std::rand() % 255, std::rand() % 255, std::rand() % 255};
            randomEnemy.picPath = "assel_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        case 2:
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 2) + 1;
            randomEnemy.health = (std::rand() % 2) + 3;
            randomEnemy.defense = {std::rand() % 100, std::rand() % 100, std::rand() % 100};
            randomEnemy.picPath = "hamster_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        case 3:
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 6) + 11;
            randomEnemy.health = (std::rand() % 4) + 13;
            randomEnemy.defense = {std::rand() % 255, std::rand() % 255, std::rand() % 255};
            randomEnemy.picPath = "mantis_warrior_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        case 4:
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 2) + 15;
            randomEnemy.health = (std::rand() % 2) + 3;
            randomEnemy.defense = {std::rand() % 50, std::rand() % 50, std::rand() % 50};
            randomEnemy.picPath = "hamster_fungus_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        
        default:
            break;
    }
    this->enemy = randomEnemy;
    return randomEnemy;
}

float FightActivity::mapInInterval(float value) {
    return (2.f/3) * (value*value) + (1.f/3) * value;
}

//This metric rewards when hitting the exact counter colors
float FightActivity::counterColorMetric(Color color) {
    int pickedColorValue;
    int weakDefenseColorValue;
    switch (color) {
        case RED:
            pickedColorValue = this->pickedColor.r;
            weakDefenseColorValue = this->enemy.defense.green;
            break;
        case GREEN:
            pickedColorValue = this->pickedColor.g;
            weakDefenseColorValue = this->enemy.defense.blue;
            break;
        case BLUE:
            pickedColorValue = this->pickedColor.b;
            weakDefenseColorValue = this->enemy.defense.red;
            break;
        default:
            break;
    }
    int deviationFromOptimal = std::max(pickedColorValue-weakDefenseColorValue, 0);
    float effectiveness = 1 - (deviationFromOptimal/ 250.f);
    return effectiveness;
}

// This metric rewards for hitting the weak spot but punishes high colors with their counter colors
float FightActivity::tugOfWarMetric(Color color) {
    int pickedColorValue;
    int weakDefenseColorValue;
    int counterDefenseColorValue;
    switch (color) {
        case RED:
            pickedColorValue = this->pickedColor.r;
            weakDefenseColorValue = this->enemy.defense.green;
            counterDefenseColorValue = this->enemy.defense.blue;
            break;
        case GREEN:
            pickedColorValue = this->pickedColor.g;
            weakDefenseColorValue = this->enemy.defense.blue;
            counterDefenseColorValue = this->enemy.defense.red;
            break;
        case BLUE:
            pickedColorValue = this->pickedColor.b;
            weakDefenseColorValue = this->enemy.defense.red;
            counterDefenseColorValue = this->enemy.defense.green;
            break;
        default:
            break;
    }
    float optimalValue = std::max((2 * weakDefenseColorValue - counterDefenseColorValue) / 2.f, 0.f);
    std::cout << "Optimal Value: " << std::to_string(optimalValue) << std::endl;
    int deviationFromOptimal = std::abs(pickedColorValue-optimalValue);
    std::cout << "Deviation from optimal: " << std::to_string(deviationFromOptimal) << std::endl;
    float effectiveness = 1 - (deviationFromOptimal/ 250.f);
    std::cout << "Effectiveness: " << std::to_string(effectiveness) << std::endl;
    return effectiveness;
}

float FightActivity::calculateSingleMultPart(Color color) {
    // Here is decided with which metric to calculated the multiplier portion
    float calulatedPortion = this->tugOfWarMetric(color);
    return mapInInterval(calulatedPortion);
}

float FightActivity::calculateAttackMult() {
    float redSummand = this->calculateSingleMultPart(RED);
    float greenSummand = this->calculateSingleMultPart(GREEN);
    float blueSummand = this->calculateSingleMultPart(BLUE);
    return (redSummand + greenSummand + blueSummand) * (this->maxMultiplier/3.f);
}