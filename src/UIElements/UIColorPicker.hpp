#ifndef UICOLORBOX_HPP
#define UICOLORBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "UIElements/UIElement.hpp"
#include "Global/Utility.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "System/GameEvents.hpp"
#include "System/Game.hpp"

class UIColorPicker: public UIElement {
  private:
    sf::Texture colorTX;
    sf::Texture borderTX;
    sf::Sprite colorSP;
    sf::Sprite borderSP;

    sf::SoundBuffer releaseSoundBuffer;

    bool pressed;

  public:
    UIColorPicker(std::string imagePath, std::string borderPath);
    UIColorPicker(sf::Image image, std::string borderPath);

    sf::Image colorIMG;
    sf::Sound releaseSound;

    void draw() override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() override;
    sf::FloatRect getSize() override;
    void scale(float x, float y) override;

    bool clickListener(sf::Vector2f &clickedPos);
    sf::Color getPixelColor(sf::Vector2f pos);
    void setColorBox(std::string picPath, std::string borderPath);
    void setColorImage(std::string picPath);
    void setColorImage(sf::Image);
    void refreshColorTX();
};

#endif