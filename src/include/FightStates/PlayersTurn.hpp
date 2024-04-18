#ifndef PLAYERSTURN_HPP
#define PLAYERSTURN_HPP

#include "FightStates/FightState.hpp"
#include "Game.hpp"

class PlayersTurn: public FightState {
  void run(Game &game) override;
};

#endif