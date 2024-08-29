#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "Activities/CharacterActivity/CharacterActivityUI.hpp"
#include "Global/Utility.hpp"

class GameUI {
  public:
    GameUI();

    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;

    CharacterActivityUI characterActivityUI;

    void changeBackgroundTexture(std::string filename);

};

#endif