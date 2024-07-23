#include "Activities/FightActivity/FightStates/EnemiesTurn.hpp"

EnemiesTurn::~EnemiesTurn() {
}

FightStateEnum EnemiesTurn::run(FightActivityUIObjects &fightActivityUIObjects) {
  Game& game = Game::getInstance();
  FightStateEnum currentState = FightStateEnum::ENEMY_STATE;
  if (!fightActivityUIObjects.enemyDamageCalculated) {
    std::random_device randSeed;
    std::mt19937 gen(randSeed());
    int minDamage = int(0.75 * fightActivityUIObjects.enemyOverview->enemy.attackStrength);
    int maxDamage = int(1.25 * fightActivityUIObjects.enemyOverview->enemy.attackStrength);
    std::uniform_int_distribution<int> dist(minDamage, maxDamage);
    int enemyDamage = dist(gen);
    int millSecToLive = 600;
    sf::Vector2f playerIconPos = fightActivityUIObjects.playerOverview->playerFrame.getPosition();
    sf::FloatRect playerIconSize = fightActivityUIObjects.playerOverview->playerFrame.getSize();
    sf::Vector2f damagePos = sf::Vector2f(playerIconPos.x + (playerIconSize.width * 0.5), playerIconPos.y + (playerIconSize.height * 0.5));

    fightActivityUIObjects.textFadingManager.startAnimation(std::to_string(enemyDamage), damagePos, sf::Color::Yellow, game.gameWindow.getSize().y * 0.05, AnimationPath::Parabel, millSecToLive);
    fightActivityUIObjects.playerOverview->changeHealth(enemyDamage);
    fightActivityUIObjects.enemyDamageCalculated = true;
  }
  if (fightActivityUIObjects.textFadingManager.fadingText.pastMillSec >= fightActivityUIObjects.textFadingManager.fadingText.millSecToLive) {
    fightActivityUIObjects.textFadingManager.fadingText.pastMillSec = 0;
    fightActivityUIObjects.isPlayersTurn = (fightActivityUIObjects.isPlayersTurn + 1) % 2;
    fightActivityUIObjects.turnSP.setTexture(fightActivityUIObjects.playersTurnTX);
    currentState = FightStateEnum::TURN_CHANGE;
  }
  return currentState;
}