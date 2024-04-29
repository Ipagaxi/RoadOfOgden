#include "FightStates/EnemiesTurn.hpp"

EnemiesTurn::~EnemiesTurn() {
}

FightStateEnum EnemiesTurn::run(FightEnv &fightEnv) {
  Game& game = Game::getInstance();
  FightStateEnum currentState = FightStateEnum::ENEMY_STATE;
  if (!fightEnv.enemyDamageCalculated) {
    std::random_device randSeed;
    std::mt19937 gen(randSeed());
    int minDamage = int(0.75 * fightEnv.enemyOverview.creature.attackStrength);
    int maxDamage = int(1.25 * fightEnv.enemyOverview.creature.attackStrength);
    std::uniform_int_distribution<int> dist(minDamage, maxDamage);
    int enemyDamage = dist(gen);
    int millSecToLive = 600;
    sf::Vector2f playerIconPos = fightEnv.playerOverview.playerFrame.getPosition();
    sf::FloatRect playerIconSize = fightEnv.playerOverview.playerFrame.getSize();
    sf::Vector2f damagePos = sf::Vector2f(playerIconPos.x + (playerIconSize.width * 0.5), playerIconPos.y + (playerIconSize.height * 0.5));

    fightEnv.textFadingManager.startAnimation(std::to_string(enemyDamage), damagePos, sf::Color::Yellow, game.gameWindow.getSize().y * 0.05, AnimationPath::Parabel, millSecToLive);
    fightEnv.playerOverview.changeHealth(enemyDamage);
    fightEnv.enemyDamageCalculated = true;
  }
  if (fightEnv.textFadingManager.fadingText.pastMillSec >= fightEnv.textFadingManager.fadingText.millSecToLive) {
    fightEnv.textFadingManager.fadingText.pastMillSec = 0;
    fightEnv.isPlayersTurn = (fightEnv.isPlayersTurn + 1) % 2;
    fightEnv.turnSP.setTexture(fightEnv.playersTurnTX);
    currentState = FightStateEnum::TURN_CHANGE;
  }
  return currentState;
}