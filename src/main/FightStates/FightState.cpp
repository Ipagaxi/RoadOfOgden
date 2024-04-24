#include "FightStates/FightState.hpp"

FightState::~FightState() {
  std::cout << "FightState destructor called!" << std::endl;
}

FightStateEnum FightState::run(Game &game, FightEnv &fightEnv) {
  return FightStateEnum::TURN_CHANGE;
}