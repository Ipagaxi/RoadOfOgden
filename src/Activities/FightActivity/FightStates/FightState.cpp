#include "Activities/FightActivity/FightStates/FightState.hpp"

FightState::~FightState() {
}

FightStateEnum FightState::run() {
  return FightStateEnum::TURN_CHANGE;
}