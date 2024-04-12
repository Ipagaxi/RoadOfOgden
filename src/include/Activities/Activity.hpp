#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameEvents.hpp"
#include "ActivityEnum.hpp"
#include "UIElements/UIButton.hpp"

class Game;

class Activity {
  public:
    Activity(Game &game);
    virtual ~Activity();
    virtual ActivityEnum executeActivity(Game &game);

  private:

  protected:
    UIButton exitButton = UIButton("buttonClose/buttonClose.png");
};

#endif