#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "UIElements/UIElement.hpp"
#include "Defines.hpp"
#include "GameState.hpp"

class UIButton: public UIElement {
    private:
        bool hovered;
        bool pressed;

        sf::Texture basicTX;
        sf::Texture clickedTX;
        sf::Texture hoveredTX;
        sf::Sprite buttonSP;

        void hoverListener(GameState &gameState);

        bool buttonContainsMouse(GameState &gameState);



    public:
        sf::Font font;
        sf::Text label;

        UIButton();
        UIButton(std::string labelText, std::string fileName, float x, float y);

        bool clickListener(GameState &gameState);

        void setPosition(float x, float y) override;
        sf::Vector2u getSize() override;

        void draw(sf::RenderWindow &window) override;
};

#endif