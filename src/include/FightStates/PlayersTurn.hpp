#ifndef PLAYERSTURN_HPP
#define PLAYERSTURN_HPP

#include "FightStates/FightState.hpp"
#include "Game.hpp"
#include "Color.hpp"
#include "GenerateColorIMG.hpp"

enum PlayerPhase {
  PICK_COLOR,
  ANIMATE_ATTACK,
  CHANGE_COLOR,
  END_TURN
};

class PlayersTurn: public FightState {
  public:
    void run(Game &game, FightEnv &fightEnv) override;

  private:
    PlayerPhase playerPhase = PlayerPhase::PICK_COLOR;
    bool colorPicked = false;
    sf::Vector2f clickedPos;

    void processAttack(FightEnv &fightEnv, Game &game);
    void changeColoPickerImage(Game &game, FightEnv &fightEnv);

    // Compute damage multiplier
    float mapInInterval(float value);
    float calculateSingleMultPart(Color color, FightEnv &fightEnv);
    float calculateAttackMult(FightEnv &fightEnv);
    // Metrics in file DamageMultMetrics.cpp
    float sameColorMetric(Color color, FightEnv &fightEnv);
    float counterColorMetric(Color color, FightEnv &fightEnv);
    float tugOfWarMetric(Color color, FightEnv &fightEnv);
};

#endif