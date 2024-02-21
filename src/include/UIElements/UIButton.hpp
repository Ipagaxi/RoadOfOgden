#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

        sf::SoundBuffer pressSoundBuffer;
        sf::SoundBuffer releaseSoundBuffer;
        sf::Sound pressSound;
        sf::Sound releaseSound;


        void init(std::string fileName);
        void hoverListener(GameState &gameState);
        bool buttonContainsMouse(GameState &gameState);



    public:
        sf::Font font;
        sf::Text label;

        UIButton();
        UIButton(std::string labelText, std::string fileName);
        UIButton(std::string fileName);

        bool clickListener(GameState &gameState);

        void setPosition(float x, float y) override;
        sf::Vector2f getPosition() override;
        sf::Vector2u getSize() override;

        void draw(sf::RenderWindow &window) override;

        void scale(float x, float y) override;
};

#endif