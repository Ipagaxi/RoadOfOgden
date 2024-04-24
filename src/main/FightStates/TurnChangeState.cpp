#include "FightStates/TurnChangeState.hpp"

TurnChangeState::~TurnChangeState() {
  std::cout << "TurnChangeState destructor called!" << std::endl;
}

FightStateEnum TurnChangeState::run(Game &game, FightEnv &fightEnv) {
  FightStateEnum currentFightState = FightStateEnum::TURN_CHANGE;
  if (!fightEnv.turnChangeBanner.runAnimation(game)) {
    if (fightEnv.isPlayersTurn) {
      currentFightState = FightStateEnum::PLAYER_STATE;
    } else {
      currentFightState = FightStateEnum::ENEMY_STATE;
    }
  }
  return currentFightState;
}