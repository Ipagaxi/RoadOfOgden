#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "Activities/CharacterActivity/CharacterActivityUI.hpp"
#include "Activities/FightActivity/FightActivityUI.hpp"
#include "Global/Utility.hpp"

class GameUI {
  public:

    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;

    CharacterActivityUI characterActivityUI;
    FightActivityUI fight_activity_ui;

    void changeBackgroundTexture(std::string filename);

    static GameUI& getInstance();
    GameUI(const GameUI&) = delete;
    GameUI operator=(const GameUI&) = delete;

  private:
    GameUI();
    ~GameUI();
    static GameUI* instance;

};

#endif