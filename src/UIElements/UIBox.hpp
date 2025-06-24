#ifndef UIBOX_HPP
#define UIBOX_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UIElements/UIElement.hpp"
#include "Global/Utility.hpp"
#include "System/Game.hpp"

/*
 *  An UIBox consist of an rectangle (often used with a transparent color) and a border
 *
 */

class UIBox : UIElement {
  public:
    UIBox(sf::Color fillColor, std::string borderFilePath);

    void draw() override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() override;
    sf::FloatRect getSize() override;
    void scale(float x, float y) override;
    void setBackgroundMargin(float x, float y);

  private:
    sf::RectangleShape backgroundREC;
    sf::Texture borderTX;
    sf::Sprite borderSP;

};

#endif