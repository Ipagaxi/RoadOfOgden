#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <string>
#include "Activities/ActivityEnum.hpp"
#include "UIElements/UIButton.hpp"

class Game;

class Activity {
  public:
    Activity();
    virtual ~Activity();
    virtual ActivityEnum executeActivity();

  private:

  protected:
    UIButton exitButton = UIButton("buttonClose/buttonClose.png");
};

#endif