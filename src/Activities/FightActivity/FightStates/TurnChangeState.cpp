#include "Activities/FightActivity/FightStates/TurnChangeState.hpp"

TurnChangeState::TurnChangeState(FightEnv &fightEnv): turnChangeBanner() {
  if (fightEnv.isPlayersTurn) {
    fightEnv.turnSP.setTexture(fightEnv.playersTurnTX);
    this->turnChangeBanner.setNewLabel("Your Turn");
  } else {
    this->turnChangeBanner.setNewLabel("Enemies Turn");
  }
}

TurnChangeState::~TurnChangeState() {
}

FightStateEnum TurnChangeState::run(FightEnv &fightEnv) {
  Game& game = Game::getInstance();
  FightStateEnum currentFightState = FightStateEnum::TURN_CHANGE;
  this->turnChangeBanner.drawAnimation();
  if (!this->turnChangeBanner.runAnimation()) {
    if (fightEnv.isPlayersTurn) {
      currentFightState = FightStateEnum::PLAYER_STATE;
    } else {
      currentFightState = FightStateEnum::ENEMY_STATE;
    }
  }
  return currentFightState;
}