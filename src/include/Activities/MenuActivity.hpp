#ifndef MENUACTIVITY_HPP
#define MENUACTIVITY_HPP

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "Game.hpp"
#include "Activities/CharacterActivity.hpp"
#include "Defines.hpp"
#include "UIElements/UIButton.hpp"

class MenuActivity: public Activity {
  public:
    MenuActivity();
    ~MenuActivity();

    ActivityEnum executeActivity() override;

  private:
    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;
    sf::Texture buttonsBackgroundTX;
    sf::Sprite buttonsBackgroundSP;
    sf::Music backgroundMusic;


    UIButton buttonFight = UIButton("Fight!", "button1/button1.png");
    UIButton buttonCharacter = UIButton("Character", "button1/button1.png");
    UIButton buttonExit = UIButton("Exit", "button1/button1.png");
};

#endif