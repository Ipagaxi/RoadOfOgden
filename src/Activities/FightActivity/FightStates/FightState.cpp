#include "Activities/FightActivity/FightStates/FightState.hpp"

FightState::~FightState() {
}

FightStateEnum FightState::run(FightEnv &fightEnv) {
  return FightStateEnum::TURN_CHANGE;
}