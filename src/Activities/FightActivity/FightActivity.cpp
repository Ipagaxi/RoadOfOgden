#include "Activities/FightActivity/FightActivity.hpp"


FightActivity::FightActivity() : Activity(), currentFightState(std::make_unique<TurnChangeState>()) {
  Game& game = Game::getInstance();
  GameUI& game_ui = GameUI::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  FightActivityUI &fight_activity_ui = game_ui.fight_activity_ui;
  this->enemy = std::make_shared<Enemy>(this->initEnemy());
  fight_activity_ui.enemyOverview = std::make_unique<UIEnemyOverview>(this->enemy);
  fight_activity_ui.playerOverview = std::make_unique<UIPlayerOverview>(game.player);

  game_ui.changeBackgroundTexture("background_fight.png");

  fight_activity_ui.backgroundMusic.openFromFile(RESOURCE_PATH + "music/fight_background_music.wav");
  fight_activity_ui.backgroundMusic.setLoop(true);
  fight_activity_ui.backgroundMusic.play();

  sf::Vector2f windowSize = static_cast<sf::Vector2f>(render_engine.gameWindow.getSize());
  sf::Vector2f backgroundSize = static_cast<sf::Vector2f>(fight_activity_ui.backgroundTX.getSize());

  sf::Vector2f backgroundScale = sf::Vector2f(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
  fight_activity_ui.backgroundSP.scale(backgroundScale);

  std::random_device randSeed;
  std::mt19937 gen(randSeed());
  std::uniform_int_distribution<int> dist(0, 1);
  fight_activity_ui.isPlayersTurn = dist(gen);

  fight_activity_ui.playersTurnTX.loadFromFile(RESOURCE_PATH + "combat/turn_status_player.png");
  fight_activity_ui.enemiesTurnTX.loadFromFile(RESOURCE_PATH + "combat/turn_status_enemy.png");

  if (fight_activity_ui.isPlayersTurn) {
    fight_activity_ui.turnSP.setTexture(fight_activity_ui.playersTurnTX);
  } else {
    fight_activity_ui.turnSP.setTexture(fight_activity_ui.enemiesTurnTX);
  }
  sf::FloatRect turnStateSignSize = fight_activity_ui.turnSP.getGlobalBounds();
  fight_activity_ui.turnSP.setPosition((windowSize.x - turnStateSignSize.width) * 0.5 , -2.0);
  this->currentFightStateEnum = FightStateEnum::TURN_CHANGE;
}

FightActivity::~FightActivity() {
  GameUI::getInstance().fight_activity_ui.backgroundMusic.stop();
}

void FightActivity::runCurrentState() {
  FightStateEnum newStateFightEnum = this->currentFightState->run();
  if (newStateFightEnum != this->currentFightStateEnum) {
    switch (newStateFightEnum) {
      case FightStateEnum::PLAYER_STATE:
        this->currentFightState = std::move(std::make_unique<PlayersTurn>());
        break;
      case FightStateEnum::ENEMY_STATE:
        this->currentFightState = std::move(std::make_unique<EnemiesTurn>());
        break;
      case FightStateEnum::TURN_CHANGE:
        this->currentFightState = std::move(std::make_unique<TurnChangeState>());
        break;
      default:
        break;
    }
    this->currentFightStateEnum = newStateFightEnum;
  }
}

ActivityEnum FightActivity::executeActivity() {
  GameUI& game_ui = GameUI::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  FightActivityUI& fight_activity_ui = game_ui.fight_activity_ui;
  ActivityEnum currentActivity = ActivityEnum::Fight;

  render_engine.gameWindow.draw(fight_activity_ui.turnSP);
  //game.gameWindow.draw(this->fightActivityUIObjects.backgroundSP);
  render_engine.gameWindow.draw(game_ui.backgroundSP);
  fight_activity_ui.playerOverview->draw();
  fight_activity_ui.enemyOverview->draw();
  this->exitButton.draw();
  fight_activity_ui.textFadingManager.run();

  this->runCurrentState();

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