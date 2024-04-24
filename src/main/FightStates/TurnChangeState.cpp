#include "FightStates/TurnChangeState.hpp"

TurnChangeState::TurnChangeState(Game &game, FightEnv &fightEnv): turnChangeBanner(game) {
  if (fightEnv.isPlayersTurn) {
    fightEnv.turnSP.setTexture(fightEnv.playersTurnTX);
    this->turnChangeBanner.setNewLabel("Your Turn");
  } else {
    this->turnChangeBanner.setNewLabel("Enemies Turn");
  }
}

TurnChangeState::~TurnChangeState() {
}

FightStateEnum TurnChangeState::run(Game &game, FightEnv &fightEnv) {
  FightStateEnum currentFightState = FightStateEnum::TURN_CHANGE;
  this->turnChangeBanner.drawAnimation(game.renderEngine.gameWindow);
  if (!this->turnChangeBanner.runAnimation(game)) {
    if (fightEnv.isPlayersTurn) {
      currentFightState = FightStateEnum::PLAYER_STATE;
    } else {
      currentFightState = FightStateEnum::ENEMY_STATE;
    }
  }
  return currentFightState;
}