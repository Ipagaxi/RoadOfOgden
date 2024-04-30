#ifndef UIENEMYOVERVIEW_HPP
#define UIENEMYOVERVIEW_HPP

#include <string>
#include <SFML/Graphics.hpp>

#include "UIElements/UIStats.hpp"
#include "UIElements/UIColorPicker.hpp"
#include "UIElements/UIBorderedImage.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Enemy.hpp"
#include "Game.hpp"

class UIEnemyOverview {
  public:
    Enemy& enemy;
    UIColorPicker colorPicker = UIColorPicker("colorPIC_default.png", "color_picker_border.png");
    sf::Text pickedColorText;

    void init(Enemy& enemy);
    void changeHealth(int value);
    void updatePickedColorText(std::string newText, sf::Color pickedColor);
    void draw();

  private:
    UIBox box = UIBox(sf::Color(51, 25, 0, 150), "borders/metal_border_900x900.png");
    sf::Texture enemyIconBackgroundTX;
    sf::Sprite enemyIconBackgroundSP;
    UIStats enemyStats;
    UIBorderedImage enemyBorderedImage;
};

#endif