#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Activities/FightActivity.hpp"
#include "Activities/Activity.hpp"

class GameState {
  private:
    std::vector<sf::Texture> initTextures ();

  public:

    GameState() {
      
    }
};

#endif