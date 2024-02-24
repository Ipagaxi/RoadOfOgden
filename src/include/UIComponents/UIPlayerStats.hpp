#ifndef UIPLAYERSTATS_HPP
#define UIPLAYERSTATS_HPP

#include "UIComponents/UIComponent.hpp"
#include "UIElements/UIBox.hpp"
#include "GameState.hpp"

class UIPlayerStats: public UIComponent {
    private:
        UIBox characterStatsBox = UIBox();
        sf::Text playerName;
        sf::Text playerHealthLabel;
        sf::Text playerHealthValue;
        sf::Text playerAttackStrengthLabel;
        sf::Text playerAttackStrengthValue;
        
    public:
        UIPlayerStats(GameState &gameState);

        void draw(sf::RenderWindow &gameWindow) override;
        sf::Vector2f getPosition() override;
        void setPosition(float x, float y) override;
        sf::FloatRect getSize() override;
};

#endif