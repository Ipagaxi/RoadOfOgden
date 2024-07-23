#include "Activities/FightActivity/FightStates/TurnChangeState.hpp"

TurnChangeState::TurnChangeState(FightActivityUIObjects &fightActivityUIObjects): turnChangeBanner() {
  if (fightActivityUIObjects.isPlayersTurn) {
    fightActivityUIObjects.turnSP.setTexture(fightActivityUIObjects.playersTurnTX);
    this->turnChangeBanner.setNewLabel("Your Turn");
  } else {
    this->turnChangeBanner.setNewLabel("Enemies Turn");
  }
}

TurnChangeState::~TurnChangeState() {
}

FightStateEnum TurnChangeState::run(FightActivityUIObjects &fightActivityUIObjects) {
  Game& game = Game::getInstance();
  FightStateEnum currentFightState = FightStateEnum::TURN_CHANGE;
  this->turnChangeBanner.drawAnimation();
  if (!this->turnChangeBanner.runAnimation()) {
    if (fightActivityUIObjects.isPlayersTurn) {
      currentFightState = FightStateEnum::PLAYER_STATE;
    } else {
      currentFightState = FightStateEnum::ENEMY_STATE;
    }
  }
  return currentFightState;
}