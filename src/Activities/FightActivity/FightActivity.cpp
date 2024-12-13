#include "Activities/FightActivity/FightActivity.hpp"


FightActivity::FightActivity() : Activity(), currentFightState(std::make_unique<TurnChangeState>()) {
  Game& game = Game::getInstance();
  GameState& game_state = GameState::getInstance();
  GameUI& game_ui = GameUI::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  FightActivityUI &fight_activity_ui = game_ui.fight_activity_ui;
  this->enemy = std::make_shared<Enemy>(this->initEnemy());
  fight_activity_ui.enemyOverview = std::make_unique<UIEnemyOverview>(this->enemy);
  fight_activity_ui.playerOverview = std::make_unique<UIPlayerOverview>(game_state.player);

  game_ui.changeBackgroundTexture("background_fight.png");

  fight_activity_ui.backgroundMusic.openFromFile(RESOURCE_PATH + "music/fight_background_music.wav");
  fight_activity_ui.backgroundMusic.setLoop(true);
  fight_activity_ui.backgroundMusic.play();

  sf::Vector2f windowSize = static_cast<sf::Vector2f>(render_engine.gameWindow.getSize());


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
        this->currentFightState = std::move(std::make_unique<PlayersTurn>(this->fight_data));
        break;
      case FightStateEnum::ENEMY_STATE:
        this->currentFightState = std::move(std::make_unique<EnemiesTurn>(this->fight_data));
        break;
      case FightStateEnum::TURN_CHANGE:
        this->currentFightState = std::move(std::make_unique<TurnChangeState>());
        break;
      case FightStateEnum::FIGHT_END:
        this->currentFightState = std::move(std::make_unique<FightEndState>(this->fight_data));
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
      randomEnemy.set_name(enemyNames[randomNum]);
      randomEnemy.set_attack_strength((std::rand() % 5) + 8);
      randomEnemy.set_health((std::rand() % 30) + 50);
      randomEnemy.set_defense({std::rand() % 150, (std::rand() % 50) + 120, std::rand() % 100});
      randomEnemy.set_pic_path("zucchini_demon_quer.png");
      randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
      break;
    case 1:
      // Assel
      randomEnemy.set_name(enemyNames[randomNum]);
      randomEnemy.set_attack_strength((std::rand() % 3) + 3);
      randomEnemy.set_health((std::rand() % 20) + 110);
      randomEnemy.set_defense({(std::rand() % 255), std::rand() % 255, std::rand() % 255});
      randomEnemy.set_pic_path("assel_quer.png");
      randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
      break;
    case 2:
      // Hamster
      randomEnemy.set_name(enemyNames[randomNum]);
      randomEnemy.set_attack_strength((std::rand() % 2) + 1);
      randomEnemy.set_health((std::rand() % 15) + 20);
      randomEnemy.set_defense({(std::rand() % 100) + 100, (std::rand() % 50) + 40, (std::rand() % 100) + 100});
      randomEnemy.set_pic_path("hamster_quer.png");
      randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
      break;
    case 3:
      // Mantis Warrior
      randomEnemy.set_name(enemyNames[randomNum]);
      randomEnemy.set_attack_strength((std::rand() % 6) + 11);
      randomEnemy.set_health((std::rand() % 15) + 90);
      randomEnemy.set_defense({std::rand() % 255, std::rand() % 255, std::rand() % 255});
      randomEnemy.set_pic_path("mantis_warrior_quer.png");
      randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
      break;
    case 4:
      // Flesh-Fungus
      randomEnemy.set_name(enemyNames[randomNum]);
      randomEnemy.set_attack_strength((std::rand() % 10) + 7);
      randomEnemy.set_health((std::rand() % 2) + 20);
      randomEnemy.set_defense({std::rand() % 80, std::rand() % 250, std::rand() % 150});
      randomEnemy.set_pic_path("hamster_fungus_quer.png");
      randomEnemy.colorPicPath = "colorPIC_" + std::to_string(randomNum) + ".png";
      break;

    default:
      break;
  }
  return randomEnemy;
}