#include "Activities/FightActivity/FightStates/TurnChangeState.hpp"

TurnChangeState::TurnChangeState(): turnChangeBanner() {
  GameUI& game_ui = GameUI::getInstance();
  FightActivityUI &fight_activity_ui = game_ui.fight_activity_ui;
  if (fight_activity_ui.isPlayersTurn) {
    fight_activity_ui.turnSP.setTexture(fight_activity_ui.playersTurnTX);
    this->turnChangeBanner.setNewLabel("Your Turn");
  } else {
    this->turnChangeBanner.setNewLabel("Enemies Turn");
  }
}

TurnChangeState::~TurnChangeState() {
}

FightStateEnum TurnChangeState::run() {
  GameUI& game_ui = GameUI::getInstance();
  FightActivityUI &fight_activity_ui = game_ui.fight_activity_ui;
  FightStateEnum currentFightState = FightStateEnum::TURN_CHANGE;
  this->turnChangeBanner.drawAnimation();
  if (!this->turnChangeBanner.runAnimation()) {
    if (fight_activity_ui.isPlayersTurn) {
      currentFightState = FightStateEnum::PLAYER_STATE;
    } else {
      currentFightState = FightStateEnum::ENEMY_STATE;
    }
  }
  return currentFightState;
}