#ifndef UIENEMYOVERVIEW_HPP
#define UIENEMYOVERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "UIComponents/UIStats.hpp"
#include "UIElements/UIColorPicker.hpp"
#include "UIElements/UIBorderedImage.hpp"
#include "Actors/Enemy.hpp"
#include "GameState.hpp"

class UIEnemyOverview {
    public:
        UIEnemyOverview(GameState &gameState, Enemy enemy);
        
        Enemy creature;
        UIColorPicker colorPicker = UIColorPicker("colorPIC_default.png", "border_color_square.png");
        
        void changeHealth(int value);
        void draw(sf::RenderWindow &gameWindow);

    private:
        sf::Texture creatureBackgroundTX;
        sf::Sprite creatureBackgroundSP;
        sf::Texture creatureBorderTX;
        sf::Sprite creatureBorderSP;
        UIStats statsComponent;
        UIBorderedImage creatureFrame;
};

#endif