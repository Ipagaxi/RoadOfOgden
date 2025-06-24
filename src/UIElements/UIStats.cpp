#include "UIElements/UIStats.hpp"

UIStats::~UIStats() {
}

UIStats::UIStats(std::shared_ptr<Actor> actor): Observer(reinterpret_cast<Subject<Actor> &>(*actor)) {
  Game& game = Game::getInstance();
  RenderEngine& render_engine = RenderEngine::getInstance();
  sf::Vector2u windowSize = render_engine.gameWindow.getSize();
  sf::Color statsValueFontColor = sf::Color::Yellow;
  sf::Color statsLabelFontColor = sf::Color::White;
  this->statsTextHeight = windowSize.y * 0.015;

  float scale = (windowSize.y * 0.4) / this->actorStatsBox.getSize().height;
  this->actorStatsBox.scale(scale, scale);

  sf::FloatRect actorStatsBoxSize = this->actorStatsBox.getSize();
  this->actorStatsBox.setBackgroundMargin(actorStatsBoxSize.width * 0.1, actorStatsBoxSize.height * 0.04);

  this->actorName.setFont(game.mainFont);
  this->actorName.setString(actor->get_name());
  this->actorName.setCharacterSize(windowSize.y*0.02);
  this->actorName.setFillColor(sf::Color::White);

  this->actorHealthLabel.setFont(game.mainFont);
  this->actorHealthLabel.setString("Health:");
  this->actorHealthLabel.setCharacterSize(statsTextHeight);
  this->actorHealthLabel.setFillColor(statsLabelFontColor);

  this->actorHealthValue.setFont(game.mainFont);
  this->actorHealthValue.setString(std::to_string(actor->get_health()));
  this->actorHealthValue.setCharacterSize(statsTextHeight);
  this->actorHealthValue.setFillColor(statsValueFontColor);

  this->actorAttackStrengthLabel.setFont(game.mainFont);
  this->actorAttackStrengthLabel.setString("ATK:");
  this->actorAttackStrengthLabel.setCharacterSize(statsTextHeight);
  this->actorAttackStrengthLabel.setFillColor(statsLabelFontColor);

  this->actorAttackStrengthValue.setFont(game.mainFont);
  this->actorAttackStrengthValue.setString(std::to_string(actor->get_attack_strength()));
  this->actorAttackStrengthValue.setCharacterSize(statsTextHeight);
  this->actorAttackStrengthValue.setFillColor(statsValueFontColor);

  this->actorRGBDefenseLabel.setFont(game.mainFont);
  this->actorRGBDefenseLabel.setString("DEF:");
  this->actorRGBDefenseLabel.setCharacterSize(statsTextHeight);
  this->actorRGBDefenseLabel.setFillColor(statsLabelFontColor);

  this->actorRGBDefenseValues.setFont(game.mainFont);
  this->actorRGBDefenseValues.setString("(" + std::to_string(actor->get_defense().red) + ", " + std::to_string(actor->get_defense().green) + ", " + std::to_string(actor->get_defense().blue) + ")");
  this->actorRGBDefenseValues.setCharacterSize(statsTextHeight);
  this->actorRGBDefenseValues.setFillColor(statsValueFontColor);

  this->setPosition(0., 0.);
}

void UIStats::draw() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  this->actorStatsBox.draw();
  render_engine.gameWindow.draw(this->actorName);
  render_engine.gameWindow.draw(this->actorHealthLabel);
  render_engine.gameWindow.draw(this->actorHealthValue);
  render_engine.gameWindow.draw(this->actorAttackStrengthLabel);
  render_engine.gameWindow.draw(this->actorAttackStrengthValue);
  render_engine.gameWindow.draw(this->actorRGBDefenseLabel);
  render_engine.gameWindow.draw(this->actorRGBDefenseValues);
}

sf::Vector2f UIStats::getPosition() {
    return this->actorStatsBox.getPosition();
}
void UIStats::setPosition(float x, float y) {
  this->actorStatsBox.setPosition(x, y);

  sf::Vector2f actorStatsBoxPosition = this->actorStatsBox.getPosition();
  sf::FloatRect actorStatsBoxSize = this->actorStatsBox.getSize();
  float statsLabelPosX = actorStatsBoxPosition.x + actorStatsBoxSize.width * 0.2;
  float statsValuePosX = actorStatsBoxPosition.x + actorStatsBoxSize.width * 0.45;
  float statsOffsetY = actorStatsBoxSize.height * 0.3;
  float statsSeparationPaddingY = actorStatsBoxSize.height * 0.05;

  std::string currentActor = this->actorName.getString();
  sf::FloatRect actorNameRec = this->actorName.getGlobalBounds();
  this->actorName.setPosition(x + ((actorStatsBoxSize.width - actorNameRec.width)/2), y + actorStatsBoxSize.height * 0.15);
  this->actorHealthLabel.setPosition(statsLabelPosX, y + statsOffsetY);
  this->actorHealthValue.setPosition(statsValuePosX, y + statsOffsetY);
  this->actorAttackStrengthLabel.setPosition(statsLabelPosX, y + statsOffsetY + statsTextHeight + statsSeparationPaddingY);
  this->actorAttackStrengthValue.setPosition(statsValuePosX, y + statsOffsetY + statsTextHeight + statsSeparationPaddingY);
  this->actorRGBDefenseLabel.setPosition(statsLabelPosX, y + statsOffsetY + (statsTextHeight + statsSeparationPaddingY)*2);
  this->actorRGBDefenseValues.setPosition(statsValuePosX, y + statsOffsetY + (statsTextHeight + statsSeparationPaddingY)*2);
}

sf::FloatRect UIStats::getSize() {
  return this->actorStatsBox.getSize();
}

void UIStats::on_notify(Actor newActor) {
  this->actorHealthValue.setString(std::to_string(newActor.get_health()));
}
