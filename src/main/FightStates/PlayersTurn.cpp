#include "FightStates/PlayersTurn.hpp"

void PlayersTurn::run(Game &game, FightEnv &fightEnv) {
  sf::Vector2f clickedPos;
  if (fightEnv.enemyOverview.colorPicker.clickListener(game.gameEvents, clickedPos)) {
    fightEnv.turnSP.setTexture(fightEnv.playersTurnTX);
    fightEnv.pickedColor = fightEnv.enemyOverview.colorPicker.getPixelColor(clickedPos);
    fightEnv.enemyOverview.updatePickedColorText("(" + std::to_string(fightEnv.pickedColor.r) +  ", " + std::to_string(fightEnv.pickedColor.g) + ", " + std::to_string(fightEnv.pickedColor.b) + ")", fightEnv.pickedColor);
    float attackMultiplier = this->calculateAttackMult(fightEnv);
    //std::cout << "Attack Multiplier: " << std::to_string(attackMultiplier) << std::endl;
    int damage = game.player.attackStrength * attackMultiplier;
    //std::cout << "Damage: " << damage << std::endl;
    fightEnv.textFadingManager.startAnimation(std::to_string(damage), clickedPos, sf::Color::Yellow, game.renderEngine.gameWindow->getSize().y * 0.05, AnimationPath::Parabel);
    fightEnv.enemyOverview.changeHealth(damage);
    fightEnv.newColorIMGNeeded = true;
  }
  if (fightEnv.textFadingManager.fadingText.pastMillSec >= fightEnv.textFadingManager.fadingText.millSecToLive) {
    fightEnv.textFadingManager.fadingText.pastMillSec = 0;
    fightEnv.isPlayersTurn = (fightEnv.isPlayersTurn + 1) % 2;
    fightEnv.enemyDamageCalculated = false;
    fightEnv.turnSP.setTexture(fightEnv.enemiesTurnTX);
    fightEnv.turnChangeBanner.setNewLabel("Enemies Turn");
    fightEnv.turnIsChanging = true;
  }
}

float PlayersTurn::mapInInterval(float value) {
  return (2.f/3) * (value*value) + (1.f/3) * value;
}

//This metric rewards when hitting the exact counter colors
float PlayersTurn::counterColorMetric(Color color, FightEnv &fightEnv) {
  int pickedColorValue;
  int weakDefenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightEnv.pickedColor.r;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.green;
      break;
    case GREEN:
      pickedColorValue = fightEnv.pickedColor.g;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.blue;
      break;
    case BLUE:
      pickedColorValue = fightEnv.pickedColor.b;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.red;
      break;
    default:
      break;
  }
  int deviationFromOptimal = std::max(pickedColorValue-weakDefenseColorValue, 0);
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  return effectiveness;
}

// This metric rewards for hitting the weak spot but punishes high colors with their counter colors
float PlayersTurn::tugOfWarMetric(Color color, FightEnv &fightEnv) {
  int pickedColorValue;
  int weakDefenseColorValue;
  int counterDefenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightEnv.pickedColor.r;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.green;
      counterDefenseColorValue = fightEnv.enemyOverview.creature.defense.blue;
      break;
    case GREEN:
      pickedColorValue = fightEnv.pickedColor.g;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.blue;
      counterDefenseColorValue = fightEnv.enemyOverview.creature.defense.red;
      break;
    case BLUE:
      pickedColorValue = fightEnv.pickedColor.b;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.red;
      counterDefenseColorValue = fightEnv.enemyOverview.creature.defense.green;
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

float PlayersTurn::calculateSingleMultPart(Color color, FightEnv &fightEnv) {
  // Here is decided with which metric to calculated the multiplier portion
  float calulatedPortion = this->tugOfWarMetric(color, fightEnv);
  return mapInInterval(calulatedPortion);
}

float PlayersTurn::calculateAttackMult(FightEnv &fightEnv) {
  float redSummand = this->calculateSingleMultPart(RED, fightEnv);
  float greenSummand = this->calculateSingleMultPart(GREEN, fightEnv);
  float blueSummand = this->calculateSingleMultPart(BLUE, fightEnv);
  return (redSummand + greenSummand + blueSummand) * (fightEnv.maxMultiplier/3.f);
}