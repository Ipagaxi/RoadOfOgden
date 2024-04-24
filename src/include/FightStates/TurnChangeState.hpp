#ifndef TURNCHANGESTATE_HPP
#define TURNCHANGESTATE_HPP

#include "FightState.hpp"
#include "FightStateEnum.hpp"

class TurnChangeState: public FightState {
  public:
    ~TurnChangeState();
    FightStateEnum run(Game &game, FightEnv &fightEnv) override;
};

#endif