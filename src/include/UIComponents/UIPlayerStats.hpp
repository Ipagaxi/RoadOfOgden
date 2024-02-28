#ifndef UIPLAYERSTATS_HPP
#define UIPLAYERSTATS_HPP

#include "UIComponents/UIComponent.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Actor.hpp"
#include "GameState.hpp"
#include <iostream>

class UIPlayerStats: public UIComponent {
    public:
        UIPlayerStats(GameState &gameState, Actor actor);

        void draw(sf::RenderWindow &gameWindow) override;
        sf::Vector2f getPosition() override;
        void setPosition(float x, float y) override;
        sf::FloatRect getSize() override;
    
    private:
        UIBox characterStatsBox;
        sf::Text playerName;
        sf::Text playerHealthLabel;
        sf::Text playerHealthValue;
        sf::Text playerAttackStrengthLabel;
        sf::Text playerAttackStrengthValue;
        float statsTextHeight;
};

#endif