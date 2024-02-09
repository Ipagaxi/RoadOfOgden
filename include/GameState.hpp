#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

//#include "Activities/FightActivity.hpp"
//#include "Activities/Activity.hpp"
#include "Textures.hpp"
#include "ActivityEnum.hpp"

class GameState {
  private:
    //std::unique_ptr<Activity> currentActivity;

  public:
    ActivityEnum currentActivity;
    Textures textures;
    sf::RenderWindow* gameWindow;

    GameState(sf::RenderWindow &window, ActivityEnum activity);

    //void changeActivity(std::unique_ptr<Activity> newActivity);
    //void displayCurrentActivity();
};

#endif