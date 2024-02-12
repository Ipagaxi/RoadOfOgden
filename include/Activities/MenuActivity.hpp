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
    sf::Texture background;
    UIButton button = UIButton("button1.png", 50., 100.);

  public:
    MenuActivity();

    void executeActivity(GameState &gameState) override;
};

#endif