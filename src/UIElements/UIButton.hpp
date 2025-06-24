#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

#include "System/GameEvents.hpp"
#include "UIElements/UIElement.hpp"
#include "Global/Utility.hpp"
#include "System/RenderEngine.hpp"
#include "System/Game.hpp"
#include "Global/Utility.hpp"

class UIButton: public UIElement {
  private:
    bool hovered;
    bool pressed;

    sf::Texture basicTX;
    sf::Texture clickedTX;
    sf::Texture hoveredTX;
    sf::Sprite buttonSP;

    sf::SoundBuffer pressSoundBuffer;
    sf::SoundBuffer releaseSoundBuffer;
    sf::Sound pressSound;
    sf::Sound releaseSound;

    void init(std::string fileName);
    void hoverListener();
    bool buttonContainsMouse();

  public:
    sf::Font font;
    sf::Text label;

    UIButton();
    UIButton(std::string labelText, std::string fileName);
    UIButton(std::string fileName);

    bool clickListener();

    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() override;
    sf::FloatRect getSize() override;

    void draw() override;

    void scale(float x, float y) override;
};

#endif