#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "GameState.hpp"
#include "ActivityEnum.hpp"

class FightActivity: public Activity {
    std::string nameEnemy = "Enemy";
  public:
    void displayActivity(GameState &gameState) override;
};

#endif