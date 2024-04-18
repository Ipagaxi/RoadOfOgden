#include "Activities/FightActivity.hpp"


FightActivity::FightActivity(Game &game) : Activity(game), fightEnv(game) {
  this->fightEnv.backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/background_fight.png");
  this->fightEnv.backgroundSP.setTexture(this->fightEnv.backgroundTX);

  this->fightEnv.backgroundMusic.openFromFile(RESOURCE_PATH "music/fight_background_music.wav");
  this->fightEnv.backgroundMusic.setLoop(true);
  this->fightEnv.backgroundMusic.play();

  sf::Vector2f windowSize = static_cast<sf::Vector2f>(game.renderEngine.gameWindow->getSize());
  sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(this->fightEnv.backgroundTX.getSize());

  sf::Vector2f backgroundScale = sf::Vector2f(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
  this->fightEnv.backgroundSP.scale(backgroundScale);

  float relativeOuterPaddingStatBoxes = 0.02;
  this->fightEnv.playerStatsBox.setPosition(windowSize.x * relativeOuterPaddingStatBoxes, (windowSize.y - this->fightEnv.playerStatsBox.getSize().height)/2);

  std::random_device randSeed;
  std::mt19937 gen(randSeed());
  std::uniform_int_distribution<int> dist(0, 1);
  this->fightEnv.isPlayersTurn = dist(gen);

  this->fightEnv.playersTurnTX.loadFromFile(RESOURCE_PATH "combat/turn_status_player.png");
  this->fightEnv.enemiesTurnTX.loadFromFile(RESOURCE_PATH "combat/turn_status_enemy.png");

  if (this->fightEnv.isPlayersTurn) {
    this->fightEnv.turnSP.setTexture(this->fightEnv.playersTurnTX);
    this->fightEnv.turnChangeBanner.setNewLabel("Your Turn");
  } else {
    this->fightEnv.turnSP.setTexture(this->fightEnv.enemiesTurnTX);
    this->fightEnv.turnChangeBanner.setNewLabel("Enemies Turn");
  }
  sf::FloatRect turnStateSignSize = this->fightEnv.turnSP.getGlobalBounds();
  this->fightEnv.turnSP.setPosition((windowSize.x - turnStateSignSize.width) * 0.5 , -2.0);
}

FightActivity::~FightActivity() {
}

void FightActivity::runEnemiesTurn(Game &game) {
  if (!this->fightEnv.enemyDamageCalculated) {
    this->fightEnv.turnIsChanging = false;
    std::random_device randSeed;
    std::mt19937 gen(randSeed());
    int minDamage = int(0.75 * this->fightEnv.enemyOverview.creature.attackStrength);
    int maxDamage = int(1.25 * this->fightEnv.enemyOverview.creature.attackStrength);
    std::uniform_int_distribution<int> dist(minDamage, maxDamage);
    int enemyDamage = dist(gen);

    sf::Vector2f playerIconPos = this->fightEnv.playerOverview.playerFrame.getPosition();
    sf::FloatRect playerIconSize = this->fightEnv.playerOverview.playerFrame.getSize();
    sf::Vector2f damagePos = sf::Vector2f(playerIconPos.x + (playerIconSize.width * 0.5), playerIconPos.y + (playerIconSize.height * 0.5));

    this->fightEnv.textFadingManager.startAnimation(std::to_string(enemyDamage), damagePos, sf::Color::Yellow, game.renderEngine.gameWindow->getSize().y * 0.05, AnimationPath::Parabel);
    this->fightEnv.playerOverview.changeHealth(enemyDamage);
    this->fightEnv.enemyDamageCalculated = true;
  }
  if (this->fightEnv.textFadingManager.fadingText.pastMillSec >= this->fightEnv.textFadingManager.fadingText.millSecToLive) {
    this->fightEnv.textFadingManager.fadingText.pastMillSec = 0;
    this->fightEnv.isPlayersTurn = (this->fightEnv.isPlayersTurn + 1) % 2;
    this->fightEnv.turnSP.setTexture(this->fightEnv.playersTurnTX);
    this->fightEnv.turnChangeBanner.setNewLabel("Your Turn");
    this->fightEnv.turnIsChanging = true;
  }
}

void FightActivity::runPlayersTurn(Game &game) {
  sf::Vector2f clickedPos;
  if (this->fightEnv.enemyOverview.colorPicker.clickListener(game.gameEvents, clickedPos)) {
    this->fightEnv.turnSP.setTexture(this->fightEnv.playersTurnTX);
    this->fightEnv.pickedColor = this->fightEnv.enemyOverview.colorPicker.getPixelColor(clickedPos);
    this->fightEnv.enemyOverview.updatePickedColorText("(" + std::to_string(this->fightEnv.pickedColor.r) +  ", " + std::to_string(fightEnv.pickedColor.g) + ", " + std::to_string(fightEnv.pickedColor.b) + ")", this->fightEnv.pickedColor);
    float attackMultiplier = this->calculateAttackMult();
    //std::cout << "Attack Multiplier: " << std::to_string(attackMultiplier) << std::endl;
    int damage = game.player.attackStrength * attackMultiplier;
    //std::cout << "Damage: " << damage << std::endl;
    this->fightEnv.textFadingManager.startAnimation(std::to_string(damage), clickedPos, sf::Color::Yellow, game.renderEngine.gameWindow->getSize().y * 0.05, AnimationPath::Parabel);
    this->fightEnv.enemyOverview.changeHealth(damage);
    this->fightEnv.newColorIMGNeeded = true;
  }
  if (this->fightEnv.textFadingManager.fadingText.pastMillSec >= this->fightEnv.textFadingManager.fadingText.millSecToLive) {
    this->fightEnv.textFadingManager.fadingText.pastMillSec = 0;
    this->fightEnv.isPlayersTurn = (this->fightEnv.isPlayersTurn + 1) % 2;
    this->fightEnv.enemyDamageCalculated = false;
    this->fightEnv.turnSP.setTexture(this->fightEnv.enemiesTurnTX);
    this->fightEnv.turnChangeBanner.setNewLabel("Enemies Turn");
    this->fightEnv.turnIsChanging = true;
  }
}

void FightActivity::runDefeat(Game &game) {
  //Here comes the Defeat
}

void FightActivity::runVictory(Game &game) {
  //Here comes the Vidtory
}

void FightActivity::runFight(Game &game) {
  if (this->fightEnv.playerOverview.player.health == 0) {
    std::cout << "Lost" << std::endl;
    this->runDefeat(game);
  } else if (this->fightEnv.enemyOverview.creature.health == 0) {
    std::cout << "Win" << std::endl;
    this->runVictory(game);
  } else if (this->fightEnv.turnIsChanging) {
    std::cout << "turn changes" << std::endl;
    this->fightEnv.turnChangeBanner.updateAnimation(game, this->fightEnv.turnIsChanging);
  } else if (this->fightEnv.isPlayersTurn) {
    std::cout << "Your turn" << std::endl;
    this->runPlayersTurn(game);
  } else {
    std::cout << "Enemies Turn" << std::endl;
    this->runEnemiesTurn(game);
  }
}

ActivityEnum FightActivity::executeActivity(Game &game) {
  sf::RenderWindow* gameWindow = game.renderEngine.gameWindow;
  ActivityEnum currentActivity = ActivityEnum::Fight;

  this->runFight(game);

  gameWindow->draw(this->fightEnv.turnSP);
  gameWindow->draw(this->fightEnv.backgroundSP);
  this->fightEnv.playerOverview.draw(gameWindow);
  this->fightEnv.enemyOverview.draw(gameWindow);
  this->exitButton.draw(gameWindow);
  this->fightEnv.textFadingManager.run(gameWindow, game.gameStatus);
  if (this->fightEnv.turnIsChanging) {
    this->fightEnv.turnChangeBanner.drawAnimation(gameWindow);
  }

  if (this->exitButton.clickListener(gameWindow, game.gameEvents)) {
    this->fightEnv.backgroundMusic.stop();
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
      pickedColorValue = this->fightEnv.pickedColor.r;
      weakDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.green;
      break;
    case GREEN:
      pickedColorValue = this->fightEnv.pickedColor.g;
      weakDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.blue;
      break;
    case BLUE:
      pickedColorValue = this->fightEnv.pickedColor.b;
      weakDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.red;
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
      pickedColorValue = this->fightEnv.pickedColor.r;
      weakDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.green;
      counterDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.blue;
      break;
    case GREEN:
      pickedColorValue = this->fightEnv.pickedColor.g;
      weakDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.blue;
      counterDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.red;
      break;
    case BLUE:
      pickedColorValue = this->fightEnv.pickedColor.b;
      weakDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.red;
      counterDefenseColorValue = this->fightEnv.enemyOverview.creature.defense.green;
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
  return (redSummand + greenSummand + blueSummand) * (this->fightEnv.maxMultiplier/3.f);
}