#ifndef UIPLAYERSTATS_HPP
#define UIPLAYERSTATS_HPP

#include <iostream>

#include "UIElements/UIBox.hpp"
#include "UIElements/UIElement.hpp"
#include "Actors/Actor.hpp"
#include "ObserverPattern/Observer.hpp"

class UIStats: public UIElement, Observer<Actor> {
  public:
    ~UIStats();
    UIStats(std::shared_ptr<Actor> actor);
    void draw() override;
    sf::Vector2f getPosition() override;
    void setPosition(float x, float y) override;
    sf::FloatRect getSize() override;

    void on_notify(Actor newActor) override;

  private:
      UIBox actorStatsBox = UIBox(sf::Color(51, 25, 0, 150), "borders/border_stats.png");
      sf::Text actorName;
      sf::Text actorHealthLabel;
      sf::Text actorAttackStrengthLabel;
      sf::Text actorRGBDefenseLabel;
      sf::Text actorHealthValue;
      sf::Text actorAttackStrengthValue;
      sf::Text actorRGBDefenseValues;
      float statsTextHeight;
      sf::Font font;
};

#endif