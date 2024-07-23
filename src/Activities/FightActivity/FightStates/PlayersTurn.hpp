#ifndef PLAYERSTURN_HPP
#define PLAYERSTURN_HPP

#include <iostream>

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "System/Game.hpp"
#include "Global/Color.hpp"
#include "Global/GenerateColorIMG.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"
#include "Global/Utility.hpp"
#include "Activities/FightActivity/FightActivityUIObjects.hpp"

enum PlayerPhase {
  PICK_COLOR,
  ANIMATE_ATTACK,
  CHANGE_COLOR,
  END_TURN
};

class PlayersTurn: public FightState {
  public:
    PlayersTurn(FightActivityUIObjects &fightActivityUIObjects);
    ~PlayersTurn();
    FightStateEnum run(FightActivityUIObjects &fightActivityUIObjects) override;

  private:
    PlayerPhase playerPhase = PlayerPhase::PICK_COLOR;
    bool colorPicked = false;
    sf::Vector2f clickedPos;
    sf::Image oldColorImage;
    sf::Image newColorImage;
    bool newColorImageSet = false;
    float passedMillSec = 0.0;

    void processAttack(FightActivityUIObjects &fightActivityUIObjects);
    void changeColoPickerImage(FightActivityUIObjects &fightActivityUIObjects);
    double computeCurrentPixel(double formerPixel, double newPixel, float elapsedRatio);

    // Compute damage multiplier
    float mapInInterval(float value);
    float calculateSingleMultPart(Color color, FightActivityUIObjects &fightActivityUIObjects);
    float calculateAttackMult(FightActivityUIObjects &fightActivityUIObjects);

    float sameColorMetric(Color color, FightActivityUIObjects &fightActivityUIObjects);
    float counterColorMetric(Color color, FightActivityUIObjects &fightActivityUIObjects);
    float tugOfWarMetric(Color color, FightActivityUIObjects &fightActivityUIObjects);
};

#endif