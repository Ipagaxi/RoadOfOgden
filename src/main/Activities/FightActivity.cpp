#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(GameState &gameState) : playerStatsBox(gameState, gameState.player), enemyOverview(gameState, initEnemy()), playerOverview(gameState) {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/background_fight.png");
    this->backgroundSP.setTexture(this->backgroundTX);

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(gameState.gameWindow->getSize());
    sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(this->backgroundTX.getSize());

    sf::Vector2f backgroundScale = sf::Vector2f(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
    this->backgroundSP.scale(backgroundScale);

    float relativeOuterPaddingStatBoxes = 0.02;
    this->playerStatsBox.setPosition(windowSize.x * relativeOuterPaddingStatBoxes, (windowSize.y - this->playerStatsBox.getSize().height)/2);

    std::random_device randSeed;
    std::mt19937 gen(randSeed());
    std::uniform_int_distribution<int> dist(0, 1);
    this->isPlayersTurn = dist(gen);

    this->playersTurnTX.loadFromFile(RESOURCE_PATH "combat/turn_status_player.png");
    this->enemiesTurnTX.loadFromFile(RESOURCE_PATH "combat/turn_status_enemy.png");

    if (this->isPlayersTurn) {
        this->turnSP.setTexture(this->playersTurnTX);
        this->turnBannerText.setString("Your Turn");
    } else {
        this->turnSP.setTexture(this->enemiesTurnTX);
        this->turnBannerText.setString("Enemies Turn");
    }
    sf::FloatRect turnStateSignSize = this->turnSP.getGlobalBounds();
    this->turnSP.setPosition((windowSize.x - turnStateSignSize.width) * 0.5 , -2.0);

    this->transparentLayer.setSize(static_cast<sf::Vector2f>(windowSize));
    this->transparentLayer.setFillColor(sf::Color(40, 40, 40, 210));

    this->turnBanner.setSize(sf::Vector2f(windowSize.x, windowSize.y * 0.2));
    this->turnBanner.setFillColor(sf::Color(40, 40, 40));

    this->turnBannerText.setFont(gameState.mainFont);
    this->turnBannerText.setCharacterSize(gameState.gameWindow->getSize().y*0.1);
    this->turnBannerText.setFillColor(sf::Color::White);
    sf::FloatRect textRec = this->turnBannerText.getGlobalBounds();
    this->turnBannerText.setOrigin(textRec.width/2, textRec.height/2);
}

void FightActivity::updateTurnChangeState(GameState &gameState) {
    int changeTimeMillSec = 2000;
    int bannerMovementime = 500;
    static int pastTimeInMillSec = 0;
    static int pastMovementTime = 0;
    float pastTimeRatio = std::min(pastMovementTime/static_cast<float>(bannerMovementime), 1.0f);
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(gameState.gameWindow->getSize());
    sf::FloatRect turnBannerSize = this->turnBanner.getGlobalBounds();
    sf::Vector2f turnBannerPos = sf::Vector2f(-windowSize.x + pastTimeRatio * windowSize.x, (windowSize.y - turnBannerSize.height) * 0.5f);
    std::cout << "Banner pos X: " << turnBannerPos.x << std::endl;
    this->turnBanner.setPosition(turnBannerPos.x, turnBannerPos.y);
    this->turnBannerText.setPosition(turnBannerPos.x + turnBannerSize.width * 0.5, turnBannerPos.y + turnBannerSize.height * 0.5);

    pastTimeInMillSec += gameState.elapsedTime.asMilliseconds();
    if (pastMovementTime < bannerMovementime) {
        pastMovementTime += gameState.elapsedTime.asMilliseconds();
    }
    if (pastTimeInMillSec >= changeTimeMillSec) {
        this->turnIsChanging = false;
        turnBannerPos = sf::Vector2f(-windowSize.x, (windowSize.y - turnBannerSize.height) * 0.5f);
        this->turnBanner.setPosition(turnBannerPos.x, turnBannerPos.y);
        this->turnBannerText.setPosition(turnBannerPos.x + turnBannerSize.width * 0.5, turnBannerPos.y + turnBannerSize.height * 0.5);
        pastTimeInMillSec = 0;
        pastMovementTime = 0;
    }
}

void FightActivity::runEnemiesTurn(GameState &gameState) {
    if (!enemyDamageCalculated) {
        this->turnIsChanging = false;
        std::random_device randSeed;
        std::mt19937 gen(randSeed());
        int minDamage = int(0.75 * this->enemyOverview.creature.attackStrength);
        int maxDamage = int(1.25 * this->enemyOverview.creature.attackStrength);
        std::uniform_int_distribution<int> dist(minDamage, maxDamage);
        int enemyDamage = dist(gen);

        sf::Vector2f playerIconPos = this->playerOverview.playerFrame.getPosition();
        sf::FloatRect playerIconSize = this->playerOverview.playerFrame.getSize();
        sf::Vector2f damagePos = sf::Vector2f(playerIconPos.x + (playerIconSize.width * 0.5), playerIconPos.y + (playerIconSize.height * 0.5));

        this->textFadingManager.startAnimation(gameState, std::to_string(enemyDamage), damagePos, sf::Color::Yellow, gameState.gameWindow->getSize().y * 0.05, 0.15, AnimationPath::Parabel);
        this->playerOverview.changeHealth(enemyDamage);
        this->enemyDamageCalculated = true;
    }
    if (this->textFadingManager.fadingText.pastMillSec >= this->textFadingManager.fadingText.millSecToLive) {
        this->textFadingManager.fadingText.pastMillSec = 0;
        this->isPlayersTurn = (this->isPlayersTurn + 1) % 2;
        this->turnSP.setTexture(this->playersTurnTX);
        this->turnBannerText.setString("Your Turn");
        sf::FloatRect turnBannerTextSize = this->turnBannerText.getGlobalBounds();
        this->turnBannerText.setOrigin(turnBannerTextSize.width * 0.5, turnBannerTextSize.height * 0.5);
        this->turnIsChanging = true;
    }
}

void FightActivity::runPlayersTurn(GameState &gameState) {
    sf::Vector2f clickedPos;
    if (this->enemyOverview.colorPicker.clickListener(gameState, clickedPos)) {
        this->turnSP.setTexture(this->playersTurnTX);
        this->pickedColor = this->enemyOverview.colorPicker.getPixelColor(clickedPos);
        this->enemyOverview.updatePickedColorText("(" + std::to_string(pickedColor.r) +  ", " + std::to_string(pickedColor.g) + ", " + std::to_string(pickedColor.b) + ")", this->pickedColor);
        float attackMultiplier = this->calculateAttackMult();
        //std::cout << "Attack Multiplier: " << std::to_string(attackMultiplier) << std::endl;
        int damage = gameState.player.attackStrength * attackMultiplier;
        //std::cout << "Damage: " << damage << std::endl;
        this->textFadingManager.startAnimation(gameState, std::to_string(damage), clickedPos, sf::Color::Yellow, gameState.gameWindow->getSize().y * 0.05, 0.15, AnimationPath::Parabel);
        this->enemyOverview.changeHealth(damage);
    }
    if (this->textFadingManager.fadingText.pastMillSec >= this->textFadingManager.fadingText.millSecToLive) {
        this->textFadingManager.fadingText.pastMillSec = 0;
        this->isPlayersTurn = (this->isPlayersTurn + 1) % 2;
        this->enemyDamageCalculated = false;
        this->turnSP.setTexture(this->enemiesTurnTX);
        this->turnBannerText.setString("Enemies Turn");
        sf::FloatRect turnBannerTextSize = this->turnBannerText.getGlobalBounds();
        this->turnBannerText.setOrigin(turnBannerTextSize.width * 0.5, turnBannerTextSize.height * 0.5);
        this->turnIsChanging = true;
    }
}

void FightActivity::runDefeat(GameState &gameState) {
    //Here comes the Defeat
}

void FightActivity::runVictory(GameState &gameState) {
    //Here comes the Vidtory
}

void FightActivity::runFight(GameState &gameState) {
    if (this->playerOverview.player.health == 0) {
        this->runDefeat(gameState);
    } else if (this->enemyOverview.creature.health == 0) {
        this->runVictory(gameState);
    } else if (this->turnIsChanging) {
        this->updateTurnChangeState(gameState);
    } else if (this->isPlayersTurn) {
        this->runPlayersTurn(gameState);
    } else {
        this->runEnemiesTurn(gameState);
    }
}

void FightActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u windowSize = window->getSize();
    sf::FloatRect buttonSize = this->exitButton.getSize();
    
    this->exitButton.setPosition(windowSize.x * 0.99 - buttonSize.width, windowSize.x * 0.01);
    this->runFight(gameState);

    window->draw(this->backgroundSP);
    window->draw(this->turnSP);
    this->playerOverview.draw(*window);
    this->enemyOverview.draw(*window);
    this->exitButton.draw(*gameState.gameWindow);
    this->textFadingManager.run(gameState);
    if (this->turnIsChanging) {
        window->draw(this->transparentLayer);
        window->draw(this->turnBanner);
        window->draw(this->turnBannerText);
    }

    if (this->exitButton.clickListener(gameState)) {
        std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>(gameState);
        gameState.setCurrentActivity(std::move(menu));
    }
}

Enemy FightActivity::initEnemy() {
    std::vector<std::string> enemyNames = {"Zucchini?!?", "Assel", "Hamster", "Mantis Warrior", "Flesh-Fungus"};
    Enemy randomEnemy;

    std::srand(std::time(nullptr));
    int randomNum = std::rand() % NUM_ENEMY;


    switch (randomNum) {
        case 0:
            // Zucchini
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 5) + 8;
            randomEnemy.health = (std::rand() % 30) + 50;
            randomEnemy.defense = {std::rand() % 150, (std::rand() % 50) + 120, std::rand() % 100};
            randomEnemy.picPath = "zucchini_demon_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        case 1:
            // Assel
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 3) + 3;
            randomEnemy.health = (std::rand() % 20) + 110;
            randomEnemy.defense = {(std::rand() % 255), std::rand() % 255, std::rand() % 255};
            randomEnemy.picPath = "assel_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        case 2:
            // Hamster
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 2) + 1;
            randomEnemy.health = (std::rand() % 15) + 20;
            randomEnemy.defense = {(std::rand() % 100) + 100, (std::rand() % 50) + 40, (std::rand() % 100) + 100};
            randomEnemy.picPath = "hamster_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        case 3:
            // Mantis Warrior
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 6) + 11;
            randomEnemy.health = (std::rand() % 15) + 90;
            randomEnemy.defense = {std::rand() % 255, std::rand() % 255, std::rand() % 255};
            randomEnemy.picPath = "mantis_warrior_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        case 4:
            // Flesh-Fungus
            randomEnemy.name = enemyNames[randomNum];
            randomEnemy.attackStrength = (std::rand() % 10) + 7;
            randomEnemy.health = (std::rand() % 2) + 20;
            randomEnemy.defense = {std::rand() % 80, std::rand() % 250, std::rand() % 150};
            randomEnemy.picPath = "hamster_fungus_quer.png";
            randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
            break;
        
        default:
            break;
    }
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
            weakDefenseColorValue = this->enemyOverview.creature.defense.green;
            break;
        case GREEN:
            pickedColorValue = this->pickedColor.g;
            weakDefenseColorValue = this->enemyOverview.creature.defense.blue;
            break;
        case BLUE:
            pickedColorValue = this->pickedColor.b;
            weakDefenseColorValue = this->enemyOverview.creature.defense.red;
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
            weakDefenseColorValue = this->enemyOverview.creature.defense.green;
            counterDefenseColorValue = this->enemyOverview.creature.defense.blue;
            break;
        case GREEN:
            pickedColorValue = this->pickedColor.g;
            weakDefenseColorValue = this->enemyOverview.creature.defense.blue;
            counterDefenseColorValue = this->enemyOverview.creature.defense.red;
            break;
        case BLUE:
            pickedColorValue = this->pickedColor.b;
            weakDefenseColorValue = this->enemyOverview.creature.defense.red;
            counterDefenseColorValue = this->enemyOverview.creature.defense.green;
            break;
        default:
            break;
    }
    float optimalValue = std::max((2 * weakDefenseColorValue - counterDefenseColorValue) / 2.f, 0.f);
    //std::cout << "Optimal Value: " << std::to_string(optimalValue) << std::endl;
    int deviationFromOptimal = std::abs(pickedColorValue-optimalValue);
    //std::cout << "Deviation from optimal: " << std::to_string(deviationFromOptimal) << std::endl;
    float effectiveness = 1 - (deviationFromOptimal/ 250.f);
    //std::cout << "Effectiveness: " << std::to_string(effectiveness) << std::endl;
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