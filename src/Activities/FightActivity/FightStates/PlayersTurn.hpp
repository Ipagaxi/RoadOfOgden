#ifndef PLAYERSTURN_HPP
#define PLAYERSTURN_HPP

#include <iostream>

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "System/Game.hpp"
#include "Global/Color.hpp"
#include "Global/GenerateColorIMG.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"

enum PlayerPhase {
  PICK_COLOR,
  ANIMATE_ATTACK,
  CHANGE_COLOR,
  END_TURN
};

class PlayersTurn: public FightState {
  public:
    PlayersTurn(FightEnv &fightEnv);
    ~PlayersTurn();
    FightStateEnum run(FightEnv &fightEnv) override;

  private:
    PlayerPhase playerPhase = PlayerPhase::PICK_COLOR;
    bool colorPicked = false;
    sf::Vector2f clickedPos;
    sf::Image oldColorImage;
    sf::Image newColorImage;
    bool newColorImageSet = false;
    float passedMillSec = 0.0;

    void processAttack(FightEnv &fightEnv);
    void changeColoPickerImage(FightEnv &fightEnv);
    double computeCurrentPixel(double formerPixel, double newPixel, float elapsedRatio);

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