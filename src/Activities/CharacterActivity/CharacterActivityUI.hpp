#ifndef CHARACTERACTIVITYUI_H
#define CHARACTERACTIVITYUI_H

#include <UIElements/UIButton.hpp>

#include "Activities/CharacterActivity/CharacterActivityUI_Inventory.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class CharacterActivityUI {
  public:
    sf::RectangleShape options_bar;
    UIButton change_to_inventory_btn = UIButton("Inventory", "button1/button1.png");
    UIButton change_to_stats_btn = UIButton("Stats", "button1/button1.png");;

    CharacterActivityUI_Inventory character_activity_ui_inventory;
};

#endif