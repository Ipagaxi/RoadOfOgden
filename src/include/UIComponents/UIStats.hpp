#ifndef UIPLAYERSTATS_HPP
#define UIPLAYERSTATS_HPP

#include "UIComponents/UIComponent.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Actor.hpp"
#include "Game.hpp"
#include <iostream>

class UIStats: public UIComponent {
    public:
        UIStats(Game &game, Actor actor);

        void setActor(Actor actor);
        void draw(sf::RenderWindow* gameWindow) override;
        sf::Vector2f getPosition() override;
        void setPosition(float x, float y) override;
        sf::FloatRect getSize() override;

        void updateHealth(int value);
    
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