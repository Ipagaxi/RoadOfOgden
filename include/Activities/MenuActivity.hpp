#ifndef MENUACTIVITY_HPP
#define MENUACTIVITY_HPP

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "GameState.hpp"
#include "Activities/FightActivity.hpp"

class MenuActivity: public Activity {
  private:
    sf::Texture background;
  public:
    MenuActivity();

    void displayActivity(GameState &gameState) override;
};

#endif