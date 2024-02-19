#ifndef MENUACTIVITY_HPP
#define MENUACTIVITY_HPP

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "GameState.hpp"
#include "Activities/FightActivity.hpp"
#include "Defines.hpp"
#include "UIElements/UIButton.hpp"

class MenuActivity: public Activity {
  private:
    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;

    UIButton button = UIButton("Fight!", "button1/button1.png");

  public:
    MenuActivity();

    void executeActivity(GameState &gameState) override;
};

#endif