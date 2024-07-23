#include "Activities/FightActivity/FightStates/PlayersTurn.hpp"

PlayersTurn::PlayersTurn(FightActivityUIObjects &fightActivityUIObjects) {
  generateTexture();
  this->newColorImage.loadFromFile(RESOURCE_PATH + "color_textures/colorPIC_new.png");
  this->oldColorImage = fightActivityUIObjects.enemyOverview->colorPicker.colorIMG;
}

PlayersTurn::~PlayersTurn() {
}

FightStateEnum PlayersTurn::run(FightActivityUIObjects &fightActivityUIObjects) {
  Game& game = Game::getInstance();
  FightStateEnum currentState = FightStateEnum::PLAYER_STATE;
  switch (this->playerPhase) {
    case PlayerPhase::PICK_COLOR:
      if (fightActivityUIObjects.enemyOverview->colorPicker.clickListener(this->clickedPos) && !colorPicked) {
        this->colorPicked = true;
        fightActivityUIObjects.turnSP.setTexture(fightActivityUIObjects.playersTurnTX);
        fightActivityUIObjects.pickedColor = fightActivityUIObjects.enemyOverview->colorPicker.getPixelColor(clickedPos);
        fightActivityUIObjects.enemyOverview->updatePickedColorText("(" + std::to_string(fightActivityUIObjects.pickedColor.r) +  ", " + std::to_string(fightActivityUIObjects.pickedColor.g) + ", " + std::to_string(fightActivityUIObjects.pickedColor.b) + ")", fightActivityUIObjects.pickedColor);
        float attackMultiplier = this->calculateAttackMult(fightActivityUIObjects);
        int damage = game.player->attackStrength * attackMultiplier;
        int millSecToLive = 600;
        fightActivityUIObjects.textFadingManager.startAnimation(std::to_string(damage), clickedPos, sf::Color::Yellow, game.gameWindow.getSize().y * 0.05, AnimationPath::Parabel, millSecToLive);
        fightActivityUIObjects.enemyOverview->changeHealth(damage);
        this->playerPhase = PlayerPhase::ANIMATE_ATTACK;
      }
      break;
    case PlayerPhase::ANIMATE_ATTACK:
      this->processAttack(fightActivityUIObjects);
      break;
    case PlayerPhase::CHANGE_COLOR:
      this->changeColoPickerImage(fightActivityUIObjects);
      break;
    case PlayerPhase::END_TURN:
      currentState = FightStateEnum::TURN_CHANGE;
      break;
  }
  return currentState;
}

void PlayersTurn::processAttack(FightActivityUIObjects &fightActivityUIObjects) {
  if (fightActivityUIObjects.textFadingManager.fadingText.pastMillSec >= fightActivityUIObjects.textFadingManager.fadingText.millSecToLive) {
    fightActivityUIObjects.textFadingManager.fadingText.pastMillSec = 0;
    fightActivityUIObjects.isPlayersTurn = (fightActivityUIObjects.isPlayersTurn + 1) % 2;
    fightActivityUIObjects.enemyDamageCalculated = false;
    fightActivityUIObjects.turnSP.setTexture(fightActivityUIObjects.enemiesTurnTX);
    this->colorPicked = false;
    this->playerPhase = PlayerPhase::CHANGE_COLOR;
  }
}

void PlayersTurn::changeColoPickerImage(FightActivityUIObjects &fightActivityUIObjects) {
  Game& game = Game::getInstance();
  static int changingMillSec = 2000;
  float elapsedRatio = this->passedMillSec/changingMillSec;
  for (int y = 0; y < GEN_IMG_HEIGHT; ++y) {
    for (int x = 0; x < GEN_IMG_WIDTH; ++x) {
      const double red = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).r, this->newColorImage.getPixel(x, y).r, elapsedRatio);
      const double green = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).g, this->newColorImage.getPixel(x, y).g, elapsedRatio);
      const double blue = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).b, this->newColorImage.getPixel(x, y).b, elapsedRatio);
      fightActivityUIObjects.enemyOverview->colorPicker.colorIMG.setPixel(x, y, sf::Color(red, green, blue));
    }
  }
  fightActivityUIObjects.enemyOverview->colorPicker.refreshColorTX();
  this->passedMillSec += game.gameStatus.elapsedTime.asMilliseconds();
  if (this->passedMillSec >= changingMillSec) {
    this->playerPhase = PlayerPhase::END_TURN;
  }
}

double PlayersTurn::computeCurrentPixel(double formerPixelColor, double newPixelColor, float elapsedRatio) {
  return formerPixelColor - ((formerPixelColor - newPixelColor) * elapsedRatio);
}

float PlayersTurn::mapInInterval(float value) {
  return (2.f/3) * (value*value) + (1.f/3) * value;
}

// This metric rewards for picking same as defense
float PlayersTurn::sameColorMetric(Color color, FightActivityUIObjects &fightActivityUIObjects) {
  int pickedColorValue;
  int defenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightActivityUIObjects.pickedColor.r;
      defenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.red;
      break;
    case GREEN:
      pickedColorValue = fightActivityUIObjects.pickedColor.g;
      defenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.green;
      break;
    case BLUE:
      pickedColorValue = fightActivityUIObjects.pickedColor.b;
      defenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.blue;
      break;
    default:
      break;
  }
  int deviationFromOptimal = std::max(pickedColorValue - defenseColorValue, 0);
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  return effectiveness;
}

//This metric rewards when hitting the exact counter colors
float PlayersTurn::counterColorMetric(Color color, FightActivityUIObjects &fightActivityUIObjects) {
  int pickedColorValue;
  int weakDefenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightActivityUIObjects.pickedColor.r;
      weakDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.green;
      break;
    case GREEN:
      pickedColorValue = fightActivityUIObjects.pickedColor.g;
      weakDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.blue;
      break;
    case BLUE:
      pickedColorValue = fightActivityUIObjects.pickedColor.b;
      weakDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.red;
      break;
    default:
      break;
  }
  int deviationFromOptimal = std::max(pickedColorValue-weakDefenseColorValue, 0);
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  return effectiveness;
}

// This metric rewards for hitting the weak spot but punishes high colors with their counter colors
float PlayersTurn::tugOfWarMetric(Color color, FightActivityUIObjects &fightActivityUIObjects) {
  int pickedColorValue;
  int weakDefenseColorValue;
  int counterDefenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightActivityUIObjects.pickedColor.r;
      weakDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.green;
      counterDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.blue;
      break;
    case GREEN:
      pickedColorValue = fightActivityUIObjects.pickedColor.g;
      weakDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.blue;
      counterDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.red;
      break;
    case BLUE:
      pickedColorValue = fightActivityUIObjects.pickedColor.b;
      weakDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.red;
      counterDefenseColorValue = fightActivityUIObjects.enemyOverview->enemy.defense.green;
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

float PlayersTurn::calculateSingleMultPart(Color color, FightActivityUIObjects &fightActivityUIObjects) {
  // Here is decided with which metric to calculated the multiplier portion
  float calulatedPortion = this->sameColorMetric(color, fightActivityUIObjects);
  return mapInInterval(calulatedPortion);
}

float PlayersTurn::calculateAttackMult(FightActivityUIObjects &fightActivityUIObjects) {
  float redSummand = this->calculateSingleMultPart(RED, fightActivityUIObjects);
  float greenSummand = this->calculateSingleMultPart(GREEN, fightActivityUIObjects);
  float blueSummand = this->calculateSingleMultPart(BLUE, fightActivityUIObjects);
  return (redSummand + greenSummand + blueSummand) * (fightActivityUIObjects.maxMultiplier/3.f);
}