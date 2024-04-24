#include "FightStates/PlayersTurn.hpp"

PlayersTurn::PlayersTurn(FightEnv &fightEnv) {
  generateTexture();
  this->newColorImage.loadFromFile(RESOURCE_PATH "color_textures/colorPIC_new.png");
  this->oldColorImage = fightEnv.enemyOverview.colorPicker.colorIMG;
}

PlayersTurn::~PlayersTurn() {
}

FightStateEnum PlayersTurn::run(Game &game, FightEnv &fightEnv) {
  FightStateEnum currentState = FightStateEnum::PLAYER_STATE;
  switch (this->playerPhase) {
    case PlayerPhase::PICK_COLOR:
      if (fightEnv.enemyOverview.colorPicker.clickListener(game.gameEvents, this->clickedPos) && !colorPicked) {
        this->colorPicked = true;
        fightEnv.turnSP.setTexture(fightEnv.playersTurnTX);
        fightEnv.pickedColor = fightEnv.enemyOverview.colorPicker.getPixelColor(clickedPos);
        fightEnv.enemyOverview.updatePickedColorText("(" + std::to_string(fightEnv.pickedColor.r) +  ", " + std::to_string(fightEnv.pickedColor.g) + ", " + std::to_string(fightEnv.pickedColor.b) + ")", fightEnv.pickedColor);
        float attackMultiplier = this->calculateAttackMult(fightEnv);
        //std::cout << "Attack Multiplier: " << std::to_string(attackMultiplier) << std::endl;
        int damage = game.player.attackStrength * attackMultiplier;
        //std::cout << "Damage: " << damage << std::endl;
        int millSecToLive = 600;
        fightEnv.textFadingManager.startAnimation(std::to_string(damage), clickedPos, sf::Color::Yellow, game.renderEngine.gameWindow->getSize().y * 0.05, AnimationPath::Parabel, millSecToLive);
        fightEnv.enemyOverview.changeHealth(damage);
        fightEnv.newColorIMGNeeded = true;
        this->playerPhase = PlayerPhase::ANIMATE_ATTACK;
      }
      break;
    case PlayerPhase::ANIMATE_ATTACK:
      this->processAttack(fightEnv, game);
      break;
    case PlayerPhase::CHANGE_COLOR:
      this->changeColoPickerImage(game, fightEnv);
      break;
    case PlayerPhase::END_TURN:
      fightEnv.turnIsChanging = true;
      currentState = FightStateEnum::TURN_CHANGE;
      break;
  }
  return currentState;
}

void PlayersTurn::processAttack(FightEnv &fightEnv, Game &game) {
  if (fightEnv.textFadingManager.fadingText.pastMillSec >= fightEnv.textFadingManager.fadingText.millSecToLive) {
    fightEnv.textFadingManager.fadingText.pastMillSec = 0;
    fightEnv.isPlayersTurn = (fightEnv.isPlayersTurn + 1) % 2;
    fightEnv.enemyDamageCalculated = false;
    fightEnv.turnSP.setTexture(fightEnv.enemiesTurnTX);
    fightEnv.turnChangeBanner.setNewLabel("Enemies Turn");
    this->colorPicked = false;
    this->playerPhase = PlayerPhase::CHANGE_COLOR;
  }
}

void PlayersTurn::changeColoPickerImage(Game &game, FightEnv &fightEnv) {
  static int changingMillSec = 3000;
  float elapsedRatio = this->passedMillSec/changingMillSec;
  for (int y = 0; y < GEN_IMG_HEIGHT; ++y) {
    for (int x = 0; x < GEN_IMG_WIDTH; ++x) {
      const double red = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).r, this->newColorImage.getPixel(x, y).r, elapsedRatio);
      const double green = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).g, this->newColorImage.getPixel(x, y).g, elapsedRatio);
      const double blue = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).b, this->newColorImage.getPixel(x, y).b, elapsedRatio);
      fightEnv.enemyOverview.colorPicker.colorIMG.setPixel(x, y, sf::Color(red, green, blue));
      if (y == 200 && x == 200) {
        //std::cout << this->oldColorImage.getPixel(y, x)
      }
    }
  }
  fightEnv.enemyOverview.colorPicker.refreshColorTX();
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
float PlayersTurn::sameColorMetric(Color color, FightEnv &fightEnv) {
  int pickedColorValue;
  int defenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightEnv.pickedColor.r;
      defenseColorValue = fightEnv.enemyOverview.creature.defense.red;
      break;
    case GREEN:
      pickedColorValue = fightEnv.pickedColor.g;
      defenseColorValue = fightEnv.enemyOverview.creature.defense.green;
      break;
    case BLUE:
      pickedColorValue = fightEnv.pickedColor.b;
      defenseColorValue = fightEnv.enemyOverview.creature.defense.blue;
      break;
    default:
      break;
  }
  int deviationFromOptimal = std::max(pickedColorValue - defenseColorValue, 0);
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  return effectiveness;
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
  float calulatedPortion = this->sameColorMetric(color, fightEnv);
  return mapInInterval(calulatedPortion);
}

float PlayersTurn::calculateAttackMult(FightEnv &fightEnv) {
  float redSummand = this->calculateSingleMultPart(RED, fightEnv);
  float greenSummand = this->calculateSingleMultPart(GREEN, fightEnv);
  float blueSummand = this->calculateSingleMultPart(BLUE, fightEnv);
  return (redSummand + greenSummand + blueSummand) * (fightEnv.maxMultiplier/3.f);
}