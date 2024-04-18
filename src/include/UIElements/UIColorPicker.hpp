#ifndef UICOLORBOX_HPP
#define UICOLORBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "UIElements/UIElement.hpp"
#include "Defines.hpp"
#include "GameEvents.hpp"
#include "Game.hpp"

class UIColorPicker: public UIElement {
  private:
    sf::Texture colorTX;
    sf::Texture borderTX;
    sf::Sprite colorSP;
    sf::Sprite borderSP;
    sf::Image colorIMG;

    sf::SoundBuffer releaseSoundBuffer;

    bool pressed;

  public:
    UIColorPicker(std::string imagePath, std::string borderPath);
    UIColorPicker(sf::Image image, std::string borderPath);

    sf::Sound releaseSound;

    void draw(sf::RenderWindow* window) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() override;
    sf::FloatRect getSize() override;
    void scale(float x, float y) override;

    bool clickListener(GameEvents &gameEvents, sf::Vector2f &clickedPos);
    sf::Color getPixelColor(sf::Vector2f pos);
    void setColorBox(std::string picPath, std::string borderPath);
    void setColorImage(std::string picPath);
};

#endif