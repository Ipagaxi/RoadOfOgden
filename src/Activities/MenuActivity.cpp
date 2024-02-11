#include "Activities/MenuActivity.hpp"

MenuActivity::MenuActivity() {
    this->background.loadFromFile(RESOURCE_PATH "menu_background.png");
    this->button = UIButton("button1.png", 50., 100.);
    this->button2 = UIButton("button1.png", 400., 300.);
}

void MenuActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Sprite backgroundSp;
    backgroundSp.setTexture(MenuActivity::background);
    button.hoverListener(gameState);
    button2.hoverListener(gameState);
    window->draw(backgroundSp);

    window->draw(this->button.buttonSP);
    window->draw(this->button2.buttonSP);

    if (button.clicked(gameState)) {
        std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>();
        gameState.setCurrentActivity(std::move(fight));
    }

    if (button2.clicked(gameState)) {
        std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>();
        gameState.setCurrentActivity(std::move(fight));
    }
}