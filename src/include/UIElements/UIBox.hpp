#ifndef UIBOX_HPP
#define UIBOX_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "UIElements/UIElement.hpp"
#include "Defines.hpp"

class UIBox : UIElement {
    private: 
        //sf::Image backgroundIMG;
        //sf::Texture backgroundTX;
        //sf::Sprite backgroundSP;
        sf::RectangleShape backgroundREC;
        sf::Texture borderTX;
        sf::Sprite borderSP;

    public:
        void draw(sf::RenderWindow &window) override;
        void setPosition(float x, float y) override;
        sf::Vector2f getPosition() override;
        sf::Vector2u getSize() override;
        void scale(float x, float y) override;

    UIBox();
};

#endif