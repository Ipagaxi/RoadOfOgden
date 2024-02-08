#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Activities/FightActivity.hpp"
#include "Activities/Activity.hpp"
#include "Textures.hpp"

class GameState {
  private:
    //std::vector<sf::Texture> initTextures ();

  public:
    Textures textures;
    sf::RenderWindow* gameWindow;

    GameState(sf::RenderWindow &window);
};

#endif