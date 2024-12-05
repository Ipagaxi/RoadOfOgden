#include "Activities/FightActivity/FightStates/PlayersTurn.hpp"

#include <Animations/TextFadingManager.hpp>

PlayersTurn::PlayersTurn() {
  FightActivityUI& fight_activity_ui = GameUI::getInstance().fight_activity_ui;
  generateTexture();
  this->newColorImage.loadFromFile(RESOURCE_PATH + "color_textures/colorPIC_new.png");
  this->oldColorImage = fight_activity_ui.enemyOverview->colorPicker.colorIMG;
}

PlayersTurn::~PlayersTurn() {
}

FightStateEnum PlayersTurn::run() {
  Game& game = Game::getInstance();
  GameState& game_state = GameState::getInstance();
  GameUI& game_ui = GameUI::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  FightActivityUI& fight_activity_ui = game_ui.fight_activity_ui;
  FightStateEnum currentState = FightStateEnum::PLAYER_STATE;
  switch (this->playerPhase) {
    case PlayerPhase::PICK_COLOR:
      if (fight_activity_ui.enemyOverview->colorPicker.clickListener(this->clickedPos) && !colorPicked) {
        this->colorPicked = true;
        fight_activity_ui.turnSP.setTexture(fight_activity_ui.playersTurnTX);
        fight_activity_ui.pickedColor = fight_activity_ui.enemyOverview->colorPicker.getPixelColor(clickedPos);
        fight_activity_ui.enemyOverview->updatePickedColorText("(" + std::to_string(fight_activity_ui.pickedColor.r) +  ", " + std::to_string(fight_activity_ui.pickedColor.g) + ", " + std::to_string(fight_activity_ui.pickedColor.b) + ")", fight_activity_ui.pickedColor);
        float attackMultiplier = this->calculateAttackMult();
        int damage = game_state.player->attackStrength * attackMultiplier;
        int millSecToLive = 600;
        fight_activity_ui.textFadingManager.startAnimation(std::to_string(damage), clickedPos, sf::Color::Yellow, render_engine.gameWindow.getSize().y * 0.05, AnimationPath::Parabel, millSecToLive);
        fight_activity_ui.enemyOverview->changeHealth(damage);
        this->playerPhase = PlayerPhase::ANIMATE_ATTACK;
      }
      break;
    case PlayerPhase::ANIMATE_ATTACK:
      this->processAttack();
      break;
    case PlayerPhase::CHANGE_COLOR:
      this->changeColoPickerImage();
      break;
    case PlayerPhase::END_TURN:
      currentState = FightStateEnum::TURN_CHANGE;
      break;
  }
  return currentState;
}

void PlayersTurn::processAttack() {
  FightActivityUI& fight_activity_ui = GameUI::getInstance().fight_activity_ui;
  if (fight_activity_ui.textFadingManager.fadingText.pastMillSec >= fight_activity_ui.textFadingManager.fadingText.millSecToLive) {
    fight_activity_ui.textFadingManager.fadingText.pastMillSec = 0;
    fight_activity_ui.isPlayersTurn = (fight_activity_ui.isPlayersTurn + 1) % 2;
    fight_activity_ui.enemyDamageCalculated = false;
    fight_activity_ui.turnSP.setTexture(fight_activity_ui.enemiesTurnTX);
    this->colorPicked = false;
    this->playerPhase = PlayerPhase::CHANGE_COLOR;
  }
}

void PlayersTurn::changeColoPickerImage() {
  Game& game = Game::getInstance();
  FightActivityUI& fight_activity_ui = GameUI::getInstance().fight_activity_ui;
  static int changingMillSec = 2000;
  float elapsedRatio = this->passedMillSec/changingMillSec;
  for (int y = 0; y < GEN_IMG_HEIGHT; ++y) {
    for (int x = 0; x < GEN_IMG_WIDTH; ++x) {
      const double red = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).r, this->newColorImage.getPixel(x, y).r, elapsedRatio);
      const double green = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).g, this->newColorImage.getPixel(x, y).g, elapsedRatio);
      const double blue = this->computeCurrentPixel(this->oldColorImage.getPixel(x, y).b, this->newColorImage.getPixel(x, y).b, elapsedRatio);
      fight_activity_ui.enemyOverview->colorPicker.colorIMG.setPixel(x, y, sf::Color(red, green, blue));
    }
  }
  fight_activity_ui.enemyOverview->colorPicker.refreshColorTX();
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
float PlayersTurn::sameColorMetric(Color color) {
  FightActivityUI& fight_activity_ui = GameUI::getInstance().fight_activity_ui;
  int pickedColorValue;
  int defenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fight_activity_ui.pickedColor.r;
      defenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.red;
      break;
    case GREEN:
      pickedColorValue = fight_activity_ui.pickedColor.g;
      defenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.green;
      break;
    case BLUE:
      pickedColorValue = fight_activity_ui.pickedColor.b;
      defenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.blue;
      break;
    default:
      break;
  }
  int deviationFromOptimal = std::max(pickedColorValue - defenseColorValue, 0);
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  return effectiveness;
}

//This metric rewards when hitting the exact counter colors
float PlayersTurn::counterColorMetric(Color color) {
  FightActivityUI& fight_activity_ui = GameUI::getInstance().fight_activity_ui;
  int pickedColorValue;
  int weakDefenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fight_activity_ui.pickedColor.r;
      weakDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.green;
      break;
    case GREEN:
      pickedColorValue = fight_activity_ui.pickedColor.g;
      weakDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.blue;
      break;
    case BLUE:
      pickedColorValue = fight_activity_ui.pickedColor.b;
      weakDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.red;
      break;
    default:
      break;
  }
  int deviationFromOptimal = std::max(pickedColorValue-weakDefenseColorValue, 0);
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  return effectiveness;
}

// This metric rewards for hitting the weak spot but punishes high colors with their counter colors
float PlayersTurn::tugOfWarMetric(Color color) {
  FightActivityUI& fight_activity_ui = GameUI::getInstance().fight_activity_ui;
  int pickedColorValue;
  int weakDefenseColorValue;
  int counterDefenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fight_activity_ui.pickedColor.r;
      weakDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.green;
      counterDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.blue;
      break;
    case GREEN:
      pickedColorValue = fight_activity_ui.pickedColor.g;
      weakDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.blue;
      counterDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.red;
      break;
    case BLUE:
      pickedColorValue = fight_activity_ui.pickedColor.b;
      weakDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.red;
      counterDefenseColorValue = fight_activity_ui.enemyOverview->enemy.defense.green;
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

float PlayersTurn::calculateSingleMultPart(Color color) {
  // Here is decided with which metric to calculated the multiplier portion
  float calulatedPortion = this->sameColorMetric(color);
  return mapInInterval(calulatedPortion);
}

float PlayersTurn::calculateAttackMult() {
  FightActivityUI& fight_activity_ui = GameUI::getInstance().fight_activity_ui;
  float redSummand = this->calculateSingleMultPart(RED);
  float greenSummand = this->calculateSingleMultPart(GREEN);
  float blueSummand = this->calculateSingleMultPart(BLUE);
  return (redSummand + greenSummand + blueSummand) * (fight_activity_ui.maxMultiplier/3.f);
}