#ifndef UIPLAYERSTATS_HPP
#define UIPLAYERSTATS_HPP

#include "UIComponents/UIComponent.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Actor.hpp"
#include "GameState.hpp"
#include <iostream>

class UIStats: public UIComponent {
    public:
        UIStats(GameState &gameState, Actor actor);

        void draw(sf::RenderWindow &gameWindow) override;
        sf::Vector2f getPosition() override;
        void setPosition(float x, float y) override;
        sf::FloatRect getSize() override;
    
    private:
        UIBox actorStatsBox;
        sf::Text actorName;
        sf::Text actorHealthLabel;
        sf::Text actorHealthValue;
        sf::Text actorAttackStrengthLabel;
        sf::Text actorAttackStrengthValue;
        float statsTextHeight;
};

#endif