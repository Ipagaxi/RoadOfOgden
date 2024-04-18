#ifndef UIENEMYOVERVIEW_HPP
#define UIENEMYOVERVIEW_HPP

#include <string>
#include <SFML/Graphics.hpp>

#include "UIComponents/UIStats.hpp"
#include "UIElements/UIColorPicker.hpp"
#include "UIElements/UIBorderedImage.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Enemy.hpp"
#include "Game.hpp"

class UIEnemyOverview {
    public:
        UIEnemyOverview(Game &game, Enemy enemy);
        UIEnemyOverview(Game &game);
        
        Enemy creature;
        UIColorPicker colorPicker = UIColorPicker("colorPIC_default.png", "color_picker_border.png");
        sf::Text pickedColorText;
        
        void changeHealth(int value);
        void updatePickedColorText(std::string newText, sf::Color pickedColor);
        void draw(sf::RenderWindow* gameWindow);

    private:
        UIBox backgroundBox = UIBox(sf::Color(51, 25, 0, 150), "borders/metal_border_900x900.png");
        sf::Texture creatureBackgroundTX;
        sf::Sprite creatureBackgroundSP;
        UIStats statsComponent;
        UIBorderedImage creatureFrame;
};

#endif