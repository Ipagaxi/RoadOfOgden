#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Activities/FightActivity.hpp"
#include "Activities/Activity.hpp"
#include "Textures.hpp"

class GameState {
  private:
    

  public:
    std::unique_ptr<Activity> currentActivity;
    Textures textures;
    sf::RenderWindow* gameWindow;

    GameState(sf::RenderWindow &window);

    void changeActivity(std::unique_ptr<Activity> newActivity);
    void startActivity(sf::RenderWindow &window, sf::Texture &background, sf::Texture &gear);
};

#endif