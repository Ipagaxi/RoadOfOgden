#ifndef CHARACTERACTIVITYUIINVENTORY_HPP
#define CHARACTERACTIVITYUIINVENTORY_HPP

#include "Inventory_Item_List.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class CharacterActivityUI_Inventory {

  public:
    CharacterActivityUI_Inventory();


    sf::Vector2f size = sf::Vector2f(0.0, 0.0);

    sf::RectangleShape left_content_box;
    sf::RectangleShape middle_content_box;
    sf::RectangleShape right_content_box;

    Inventory_Item_List inventory_item_list;

    void draw();
    void set_position(sf::Vector2f new_pos);

  private:
    float content_box_gap;
    sf::Vector2f position;
};

#endif
