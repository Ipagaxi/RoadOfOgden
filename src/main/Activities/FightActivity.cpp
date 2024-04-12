#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(Game &game) : Activity(game), playerStatsBox(game, game.player), enemyOverview(game, initEnemy()), playerOverview(game), turnChangeBanner(game) {
  this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/background_fight.png");
  this->backgroundSP.setTexture(this->backgroundTX);

  this->backgroundMusic.openFromFile(RESOURCE_PATH "music/fight_background_music.wav");
  this->backgroundMusic.setLoop(true);
  this->backgroundMusic.play();

  sf::Vector2f windowSize = static_cast<sf::Vector2f>(game.renderEngine.gameWindow->getSize());
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
    this->turnChangeBanner.setNewLabel("Your Turn");
  } else {
    this->turnSP.setTexture(this->enemiesTurnTX);
    this->turnChangeBanner.setNewLabel("Enemies Turn");
  }
  sf::FloatRect turnStateSignSize = this->turnSP.getGlobalBounds();
  this->turnSP.setPosition((windowSize.x - turnStateSignSize.width) * 0.5 , -2.0);
}

FightActivity::~FightActivity() {
}

void FightActivity::runEnemiesTurn(Game &game) {
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

    this->textFadingManager.startAnimation(std::to_string(enemyDamage), damagePos, sf::Color::Yellow, game.renderEngine.gameWindow->getSize().y * 0.05, AnimationPath::Parabel);
    this->playerOverview.changeHealth(enemyDamage);
    this->enemyDamageCalculated = true;
  }
  if (this->textFadingManager.fadingText.pastMillSec >= this->textFadingManager.fadingText.millSecToLive) {
    this->textFadingManager.fadingText.pastMillSec = 0;
    this->isPlayersTurn = (this->isPlayersTurn + 1) % 2;
    this->turnSP.setTexture(this->playersTurnTX);
    this->turnChangeBanner.setNewLabel("Your Turn");
    this->turnIsChanging = true;
  }
}

void FightActivity::runPlayersTurn(Game &game) {
  sf::Vector2f clickedPos;
  if (this->enemyOverview.colorPicker.clickListener(game.gameEvents, clickedPos)) {
    this->turnSP.setTexture(this->playersTurnTX);
    this->pickedColor = this->enemyOverview.colorPicker.getPixelColor(clickedPos);
    this->enemyOverview.updatePickedColorText("(" + std::to_string(pickedColor.r) +  ", " + std::to_string(pickedColor.g) + ", " + std::to_string(pickedColor.b) + ")", this->pickedColor);
    float attackMultiplier = this->calculateAttackMult();
    //std::cout << "Attack Multiplier: " << std::to_string(attackMultiplier) << std::endl;
    int damage = game.player.attackStrength * attackMultiplier;
    //std::cout << "Damage: " << damage << std::endl;
    this->textFadingManager.startAnimation(std::to_string(damage), clickedPos, sf::Color::Yellow, game.renderEngine.gameWindow->getSize().y * 0.05, AnimationPath::Parabel);
    this->enemyOverview.changeHealth(damage);
  }
  if (this->textFadingManager.fadingText.pastMillSec >= this->textFadingManager.fadingText.millSecToLive) {
    this->textFadingManager.fadingText.pastMillSec = 0;
    this->isPlayersTurn = (this->isPlayersTurn + 1) % 2;
    this->enemyDamageCalculated = false;
    this->turnSP.setTexture(this->enemiesTurnTX);
    this->turnChangeBanner.setNewLabel("Enemies Turn");
    this->turnIsChanging = true;
  }
}

void FightActivity::runDefeat(Game &game) {
  //Here comes the Defeat
}

void FightActivity::runVictory(Game &game) {
  //Here comes the Vidtory
}

void FightActivity::runFight(Game &game) {
  if (this->playerOverview.player.health == 0) {
    this->runDefeat(game);
  } else if (this->enemyOverview.creature.health == 0) {
    this->runVictory(game);
  } else if (this->turnIsChanging) {
    this->turnChangeBanner.updateAnimation(game, this->turnIsChanging);
  } else if (this->isPlayersTurn) {
    this->runPlayersTurn(game);
  } else {
    this->runEnemiesTurn(game);
  }
}

ActivityEnum FightActivity::executeActivity(Game &game) {
  sf::RenderWindow* gameWindow = game.renderEngine.gameWindow;
  ActivityEnum currentActivity = ActivityEnum::Fight;

  this->runFight(game);

  gameWindow->draw(this->turnSP);
  gameWindow->draw(this->backgroundSP);
  this->playerOverview.draw(gameWindow);
  this->enemyOverview.draw(gameWindow);
  this->exitButton.draw(gameWindow);
  this->textFadingManager.run(gameWindow, game.gameStatus);
  if (this->turnIsChanging) {
    this->turnChangeBanner.drawAnimation(gameWindow);
  }

  if (this->exitButton.clickListener(gameWindow, game.gameEvents)) {
    this->backgroundMusic.stop();
    currentActivity = ActivityEnum::Menu;
  }
  return currentActivity;
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