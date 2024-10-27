#include "CharacterActivity.hpp"

#include <System/GameUI.hpp>

CharacterActivity::CharacterActivity(): Activity() {
  GameUI& game_ui = GameUI::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  CharacterActivityUI& character_activity_ui = game_ui.characterActivityUI;

  game_ui.changeBackgroundTexture("backgroundMenu.png");

  sf::Vector2f windowSize = static_cast<sf::Vector2f>(render_engine.gameWindow.getSize());
  character_activity_ui.options_bar.setSize(sf::Vector2f(windowSize.x * 0.8, windowSize.y * 0.08));
  sf::FloatRect options_bar_bounds = character_activity_ui.options_bar.getGlobalBounds();
  sf::Vector2f options_bar_pos = sf::Vector2f((windowSize.x - options_bar_bounds.width)*0.5, 0.02 * windowSize.y);
  character_activity_ui.options_bar.setPosition(options_bar_pos);
  character_activity_ui.options_bar.setFillColor(sf::Color(0, 0, 0, 180));

  float options_bar_gap = windowSize.x * 0.03;
  sf::FloatRect options_bar_btn_size = character_activity_ui.change_to_inventory_btn.getSize();
  float options_bar_btn_pos_y = options_bar_pos.y + (options_bar_bounds.height - options_bar_btn_size.height) * 0.5;

  character_activity_ui.change_to_inventory_btn.setPosition(options_bar_pos.x + options_bar_gap, options_bar_btn_pos_y);
  character_activity_ui.change_to_stats_btn.setPosition(options_bar_pos.x + options_bar_gap * 2 + options_bar_btn_size.width, options_bar_btn_pos_y);

  character_activity_ui.character_activity_ui_inventory.set_position(sf::Vector2f((windowSize.x - character_activity_ui.character_activity_ui_inventory.size.x) * 0.5, options_bar_pos.y + options_bar_bounds.height + windowSize.y * 0.05));
}

void CharacterActivity::draw_ui() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  GameUI& game_ui = GameUI::getInstance();

  render_engine.gameWindow.draw(game_ui.backgroundSP);
  this->exitButton.draw();
  render_engine.gameWindow.draw(game_ui.characterActivityUI.options_bar);
  game_ui.characterActivityUI.change_to_inventory_btn.draw();
  game_ui.characterActivityUI.change_to_stats_btn.draw();

  game_ui.characterActivityUI.character_activity_ui_inventory.draw();
}


ActivityEnum CharacterActivity::executeActivity() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  GameUI& game_ui = GameUI::getInstance();

  this->draw_ui();

  ActivityEnum currentActivity = ActivityEnum::Character;
  if (this->exitButton.clickListener()) {
    currentActivity = ActivityEnum::Menu;
  }
  return currentActivity;
}