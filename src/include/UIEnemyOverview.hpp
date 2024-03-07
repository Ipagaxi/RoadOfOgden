#ifndef UIENEMYOVERVIEW_HPP
#define UIENEMYOVERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "UIComponents/UIStats.hpp"
#include "UIElements/UIColorPicker.hpp"
#include "UIElements/UIBorderedImage.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Enemy.hpp"
#include "GameState.hpp"

class UIEnemyOverview {
    public:
        UIEnemyOverview(GameState &gameState, Enemy enemy);
        
        Enemy creature;
        UIColorPicker colorPicker = UIColorPicker("colorPIC_default.png", "border_square.png");
        
        void changeHealth(int value);
        void draw(sf::RenderWindow &gameWindow);

    private:
        UIBox backgroundBox = UIBox(sf::Color(51, 25, 0, 150), "borders/metal_border_900x900.png");
        sf::Texture creatureBackgroundTX;
        sf::Sprite creatureBackgroundSP;
        UIStats statsComponent;
        UIBorderedImage creatureFrame;
};

#endif