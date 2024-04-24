#include "FightStates/FightState.hpp"

FightState::~FightState() {
}

FightStateEnum FightState::run(Game &game, FightEnv &fightEnv) {
  return FightStateEnum::TURN_CHANGE;
}