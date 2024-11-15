#include "CharacterActivityUI_Inventory.hpp"

#include <System/RenderEngine.hpp>

CharacterActivityUI_Inventory::CharacterActivityUI_Inventory() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  sf::Vector2f window_size = static_cast<sf::Vector2f>(render_engine.gameWindow.getSize());

  sf::Vector2f content_box_size = sf::Vector2f(window_size.x * 0.3, window_size.y * 0.8);
  this->content_box_gap = window_size.x * 0.02;

  this->left_content_box.setSize(content_box_size);
  this->left_content_box.setPosition(this->position);
  this->left_content_box.setFillColor(sf::Color(0, 0, 0, 180));

  double left_content_box_width = this->left_content_box.getGlobalBounds().width;
  double item_image_width = this->item_image.getSize().width;
  double item_image_scale = (0.45 * left_content_box_width) / item_image_width;
  this->item_image.scale(item_image_scale, item_image_scale);
  sf::Vector2f left_content_box_pos = this->left_content_box.getPosition();
  sf::Vector2f item_image_position = sf::Vector2f(left_content_box_pos.x + this->left_content_box.getGlobalBounds().width * 0.5, left_content_box_pos.y * this->left_content_box.getGlobalBounds().height * 0.1);
  this->item_image.setPosition(0.0, 0.0);

  this->middle_content_box.setSize(content_box_size);
  this->middle_content_box.setPosition(this->position.x + content_box_size.x + this->content_box_gap, this->position.y);
  this->middle_content_box.setFillColor(sf::Color(0, 0, 0, 180));

  this->right_content_box.setSize(content_box_size);
  this->right_content_box.setPosition(this->position.x + content_box_size.x * 2 + this->content_box_gap * 2, this->position.y);
  this->right_content_box.setFillColor(sf::Color(0, 0, 0, 180));

  this->size = sf::Vector2f(content_box_size.x * 3 + this->content_box_gap * 2, content_box_size.y);

  inventory_item_list.set_position(this->position.x, this->position.y);
}

void CharacterActivityUI_Inventory::draw() {
  RenderEngine& render_engine = RenderEngine::getInstance();

  render_engine.gameWindow.draw(this->left_content_box);
  render_engine.gameWindow.draw(this->middle_content_box);
  render_engine.gameWindow.draw(this->right_content_box);

  this->item_image.draw();

  this->inventory_item_list.draw();
}

void CharacterActivityUI_Inventory::set_position(sf::Vector2f new_pos) {
  sf::FloatRect content_box_size = this->left_content_box.getGlobalBounds();

  this->position = new_pos;
  this->inventory_item_list.set_position(new_pos.x, new_pos.y);

  this->left_content_box.setPosition(new_pos);
  this->middle_content_box.setPosition(new_pos.x + content_box_size.width + this->content_box_gap, new_pos.y);
  this->right_content_box.setPosition(new_pos.x + content_box_size.width * 2 + this->content_box_gap * 2, new_pos.y);
}


