#include "Activities/FightActivity/FightStates/EnemiesTurn.hpp"

#include <Animations/TextFadingManager.hpp>

EnemiesTurn::~EnemiesTurn() {
}

FightStateEnum EnemiesTurn::run() {
  GameUI& game_ui = GameUI::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  FightActivityUI& fight_activity_ui = game_ui.fight_activity_ui;
  FightStateEnum currentState = FightStateEnum::ENEMY_STATE;
  if (!fight_activity_ui.enemyDamageCalculated) {
    std::random_device randSeed;
    std::mt19937 gen(randSeed());
    int minDamage = int(0.75 * fight_activity_ui.enemyOverview->enemy.attackStrength);
    int maxDamage = int(1.25 * fight_activity_ui.enemyOverview->enemy.attackStrength);
    std::uniform_int_distribution<int> dist(minDamage, maxDamage);
    int enemyDamage = dist(gen);
    int millSecToLive = 600;
    sf::Vector2f playerIconPos = fight_activity_ui.playerOverview->playerFrame.getPosition();
    sf::FloatRect playerIconSize = fight_activity_ui.playerOverview->playerFrame.getSize();
    sf::Vector2f damagePos = sf::Vector2f(playerIconPos.x + (playerIconSize.width * 0.5), playerIconPos.y + (playerIconSize.height * 0.5));

    fight_activity_ui.textFadingManager.startAnimation(std::to_string(enemyDamage), damagePos, sf::Color::Yellow, render_engine.gameWindow.getSize().y * 0.05, AnimationPath::Parabel, millSecToLive);
    fight_activity_ui.playerOverview->changeHealth(enemyDamage);
    fight_activity_ui.enemyDamageCalculated = true;
  }
  if (fight_activity_ui.textFadingManager.fadingText.pastMillSec >= fight_activity_ui.textFadingManager.fadingText.millSecToLive) {
    fight_activity_ui.textFadingManager.fadingText.pastMillSec = 0;
    fight_activity_ui.isPlayersTurn = (fight_activity_ui.isPlayersTurn + 1) % 2;
    fight_activity_ui.turnSP.setTexture(fight_activity_ui.playersTurnTX);
    currentState = FightStateEnum::TURN_CHANGE;
  }
  return currentState;
}