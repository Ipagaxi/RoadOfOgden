#ifndef TURNCHANGESTATE_HPP
#define TURNCHANGESTATE_HPP

#include "FightState.hpp"
#include "FightStateEnum.hpp"
#include "Animations/IncomingBanner.hpp"
#include "Game.hpp"

class TurnChangeState: public FightState {
  public:
    TurnChangeState(FightEnv &fightEnv);
    ~TurnChangeState();
    FightStateEnum run(FightEnv &fightEnv) override;

  private:
    IncomingBanner turnChangeBanner;

};

#endif