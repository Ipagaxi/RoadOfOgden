#ifndef INVENTORY_ITEM_LIST_HPP
#define INVENTORY_ITEM_LIST_HPP

#include <list>
#include <cmath>

#include "Items/Item.hpp"
#include "SFML/Graphics/View.hpp"

class Inventory_Item_List {
  public:
    Inventory_Item_List();

    void draw();
    void set_position(float x_pos, float y_pos);

  private:
    std::list<Item> items;
    sf::Vector2f size;
    sf::Vector2f position;
    float item_font_size;
    float item_gap;
    int index_of_first_visible_item = 0;
};

#endif
