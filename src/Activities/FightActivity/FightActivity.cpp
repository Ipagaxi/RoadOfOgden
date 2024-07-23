#include "Activities/FightActivity/FightActivity.hpp"


FightActivity::FightActivity() : Activity(), fightActivityUIObjects(), currentFightState(std::make_unique<TurnChangeState>(fightActivityUIObjects)) {
  Game& game = Game::getInstance();
  this->enemy = std::make_shared<Enemy>(this->initEnemy());
  this->fightActivityUIObjects.enemyOverview = std::make_unique<UIEnemyOverview>(this->enemy);
  this->fightActivityUIObjects.playerOverview = std::make_unique<UIPlayerOverview>(Game::getInstance().player);

  this->fightActivityUIObjects.backgroundTX.loadFromFile(RESOURCE_PATH + "backgrounds/background_fight.png");
  this->fightActivityUIObjects.backgroundSP.setTexture(this->fightActivityUIObjects.backgroundTX);

  this->fightActivityUIObjects.backgroundMusic.openFromFile(RESOURCE_PATH + "music/fight_background_music.wav");
  this->fightActivityUIObjects.backgroundMusic.setLoop(true);
  this->fightActivityUIObjects.backgroundMusic.play();

  sf::Vector2f windowSize = static_cast<sf::Vector2f>(game.gameWindow.getSize());
  sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(this->fightActivityUIObjects.backgroundTX.getSize());

  sf::Vector2f backgroundScale = sf::Vector2f(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
  this->fightActivityUIObjects.backgroundSP.scale(backgroundScale);

  std::random_device randSeed;
  std::mt19937 gen(randSeed());
  std::uniform_int_distribution<int> dist(0, 1);
  this->fightActivityUIObjects.isPlayersTurn = dist(gen);

  this->fightActivityUIObjects.playersTurnTX.loadFromFile(RESOURCE_PATH + "combat/turn_status_player.png");
  this->fightActivityUIObjects.enemiesTurnTX.loadFromFile(RESOURCE_PATH + "combat/turn_status_enemy.png");

  if (this->fightActivityUIObjects.isPlayersTurn) {
    this->fightActivityUIObjects.turnSP.setTexture(this->fightActivityUIObjects.playersTurnTX);
  } else {
    this->fightActivityUIObjects.turnSP.setTexture(this->fightActivityUIObjects.enemiesTurnTX);
  }
  sf::FloatRect turnStateSignSize = this->fightActivityUIObjects.turnSP.getGlobalBounds();
  this->fightActivityUIObjects.turnSP.setPosition((windowSize.x - turnStateSignSize.width) * 0.5 , -2.0);
  this->currentFightStateEnum = FightStateEnum::TURN_CHANGE;
}

FightActivity::~FightActivity() {
  this->fightActivityUIObjects.backgroundMusic.stop();
}

void FightActivity::runCurrentState(Game &game) {
  FightStateEnum newStateFightEnum = this->currentFightState->run(this->fightActivityUIObjects);
  if (newStateFightEnum != this->currentFightStateEnum) {
    switch (newStateFightEnum) {
      case FightStateEnum::PLAYER_STATE:
        this->currentFightState = std::move(std::make_unique<PlayersTurn>(this->fightActivityUIObjects));
        break;
      case FightStateEnum::ENEMY_STATE:
        this->currentFightState = std::move(std::make_unique<EnemiesTurn>());
        break;
      case FightStateEnum::TURN_CHANGE:
        this->currentFightState = std::move(std::make_unique<TurnChangeState>(this->fightActivityUIObjects));
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

  game.gameWindow.draw(this->fightActivityUIObjects.turnSP);
  game.gameWindow.draw(this->fightActivityUIObjects.backgroundSP);
  this->fightActivityUIObjects.playerOverview->draw();
  this->fightActivityUIObjects.enemyOverview->draw();
  this->exitButton.draw();
  this->fightActivityUIObjects.textFadingManager.run();

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