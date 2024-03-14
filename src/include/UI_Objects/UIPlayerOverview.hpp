#ifndef UIPLAYEROVERVIEW_HPP
#define UIPLAYEROVERVIEW_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>

#include "GameState.hpp"
#include "UIElements/UIBox.hpp"
#include "UIElements/UIBorderedImage.hpp"
#include "UIComponents/UIStats.hpp"


class UIPlayerOverview {
    public:
        UIPlayerOverview(GameState &gameState);

        UIBorderedImage playerFrame;
        Player player;

        void changeHealth(int value);
        void draw(sf::RenderWindow &gameWindow);

    private:
        UIBox backgroundBox = UIBox(sf::Color(51, 25, 0, 150), "borders/metal_border_900x900.png");
        sf::Texture playerBackgroundTX;
        sf::Sprite playerBackgroundSP;
        UIStats statsComponent;
};

#endif