#include "Inventory_Item_List.hpp"

#include <System/Game.hpp>
#include <System/RenderEngine.hpp>

Inventory_Item_List::Inventory_Item_List() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  sf::Vector2f window_size = static_cast<sf::Vector2f>(render_engine.gameWindow.getSize());

  this->size = sf::Vector2f(window_size.x * 0.2, window_size.y * 0.4);
  this->item_gap = this->size.y * 0.05;
  this->item_font_size = this->size.y * 0.05;

  this->items.push_back(Item());
  this->items.push_back(Item());
  this->items.push_back(Item());
}


void Inventory_Item_List::draw() {
  Game& game = Game::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  sf::RenderWindow& game_window = render_engine.gameWindow;
  //int number_visible_items = (int) (this->size.y / (this->item_font_size + this->item_gap));
  sf::Text item_name = sf::Text(this->items.front().name, game.mainFont, this->item_font_size);
  float offset_first_item = this->size.x * 0.05;
  item_name.setPosition(this->position.x + offset_first_item, this->position.y + offset_first_item);
  std::cout << "Num. items: " << items.size() << std::endl;

  for (std::list<Item>::iterator it=this->items.begin(); it != items.end() && item_name.getPosition().y + item_font_size < this->position.y + this->size.y; ++it) {
    item_name.setString(it->name);
    game_window.draw(item_name);
    std::cout << "Item drawn to : " << item_name.getPosition().y << std::endl;
    item_name.move(0, item_font_size + item_gap);
  }
}


void Inventory_Item_List::set_position(float x_pos, float y_pos) {
  this->position = sf::Vector2f(x_pos, y_pos);
}

