#ifndef PLAYERSTURN_HPP
#define PLAYERSTURN_HPP

#include <iostream>

#include "FightStates/FightState.hpp"
#include "Game.hpp"
#include "Color.hpp"
#include "GenerateColorIMG.hpp"
#include "FightStateEnum.hpp"

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
    FightStateEnum run(Game &game, FightEnv &fightEnv) override;

  private:
    PlayerPhase playerPhase = PlayerPhase::PICK_COLOR;
    bool colorPicked = false;
    sf::Vector2f clickedPos;
    sf::Image oldColorImage;
    sf::Image newColorImage;
    bool newColorImageSet = false;
    float passedMillSec = 0.0;

    void processAttack(FightEnv &fightEnv, Game &game);
    void changeColoPickerImage(Game &game, FightEnv &fightEnv);
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