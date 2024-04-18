#ifndef PLAYERSTURN_HPP
#define PLAYERSTURN_HPP

#include "FightStates/FightState.hpp"
#include "Game.hpp"
#include "Color.hpp"

class PlayersTurn: public FightState {
  public:
    void run(Game &game, FightEnv &fightEnv) override;

  private:
    // Compute damage multiplier
    float mapInInterval(float value);
    float calculateSingleMultPart(Color color, FightEnv &fightEnv);
    float calculateAttackMult(FightEnv &fightEnv);
    // Metrics in file DamageMultMetrics.cpp
    float counterColorMetric(Color color, FightEnv &fightEnv);
    float tugOfWarMetric(Color color, FightEnv &fightEnv);
};

#endif