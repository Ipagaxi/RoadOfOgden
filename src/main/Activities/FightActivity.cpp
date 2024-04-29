#include "Activities/FightActivity.hpp"


FightActivity::FightActivity() : Activity(), fightEnv(), currentFightState(std::make_unique<TurnChangeState>(fightEnv)) {
  Game& game = Game::getInstance();
  this->fightEnv.enemyOverview.setEnemy(initEnemy());
  this->fightEnv.backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/background_fight.png");
  this->fightEnv.backgroundSP.setTexture(this->fightEnv.backgroundTX);

  this->fightEnv.backgroundMusic.openFromFile(RESOURCE_PATH "music/fight_background_music.wav");
  this->fightEnv.backgroundMusic.setLoop(true);
  this->fightEnv.backgroundMusic.play();

  sf::Vector2f windowSize = static_cast<sf::Vector2f>(game.gameWindow.getSize());
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
  } else {
    this->fightEnv.turnSP.setTexture(this->fightEnv.enemiesTurnTX);
  }
  sf::FloatRect turnStateSignSize = this->fightEnv.turnSP.getGlobalBounds();
  this->fightEnv.turnSP.setPosition((windowSize.x - turnStateSignSize.width) * 0.5 , -2.0);
  this->currentFightStateEnum = FightStateEnum::TURN_CHANGE;
}

FightActivity::~FightActivity() {
  this->fightEnv.backgroundMusic.stop();
}

void FightActivity::runCurrentState(Game &game) {
  FightStateEnum newStateFightEnum = this->currentFightState->run(this->fightEnv);
  if (newStateFightEnum != this->currentFightStateEnum) {
    switch (newStateFightEnum) {
      case FightStateEnum::PLAYER_STATE:
        this->currentFightState = std::move(std::make_unique<PlayersTurn>(this->fightEnv));
        break;
      case FightStateEnum::ENEMY_STATE:
        this->currentFightState = std::move(std::make_unique<EnemiesTurn>());
        break;
      case FightStateEnum::TURN_CHANGE:
        this->currentFightState = std::move(std::make_unique<TurnChangeState>(this->fightEnv));
        break;
      default:
        break;
    }
    this->currentFightStateEnum = newStateFightEnum;
  }
}

ActivityEnum FightActivity::executeActivity() {
  Game& game = Game::getInstance();
  ActivityEnum currentActivity = ActivityEnum::Fight;

  game.gameWindow.draw(this->fightEnv.turnSP);
  game.gameWindow.draw(this->fightEnv.backgroundSP);
  this->fightEnv.playerOverview.draw();
  this->fightEnv.enemyOverview.draw();
  this->exitButton.draw();
  this->fightEnv.textFadingManager.run();

  this->runCurrentState(game);

  if (this->exitButton.clickListener()) {

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