#include "Activities/FightActivity/FightStates/FightState.hpp"

FightState::~FightState() {
}

FightStateEnum FightState::run(FightActivityUIObjects &fightActivityUIObjects) {
  return FightStateEnum::TURN_CHANGE;
}