#ifndef UIENEMYOVERVIEW_HPP
#define UIENEMYOVERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "UIComponents/UIStats.hpp"
#include "UIElements/UIColorBox.hpp"
#include "Actors/Enemy.hpp"
#include "GameState.hpp"

class UIEnemyOverview {
    public:
        UIEnemyOverview(GameState &gameState, Enemy enemy);
        
        Enemy creature;
        UIColorBox colorPicker = UIColorBox("colorPIC_default.png", "border_color_square.png");
        
        void changeHealth(int value);
        void draw(sf::RenderWindow &gameWindow);

    private:
        sf::Texture creatureTX;
        sf::Sprite creatureSP;
        UIStats statsComponent;
};

#endif