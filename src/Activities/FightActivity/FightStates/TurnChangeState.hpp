#ifndef TURNCHANGESTATE_HPP
#define TURNCHANGESTATE_HPP

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"
#include "Animations/IncomingBanner.hpp"
#include "System/Game.hpp"

class TurnChangeState: public FightState {
  public:
    TurnChangeState(FightEnv &fightEnv);
    ~TurnChangeState();
    FightStateEnum run(FightEnv &fightEnv) override;

  private:
    IncomingBanner turnChangeBanner;

};

#endif