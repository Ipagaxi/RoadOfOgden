#include "Activities/MenuActivity.hpp"

MenuActivity::MenuActivity() {
    this->background.loadFromFile(RESOURCE_PATH "menu_background.png");
}

void MenuActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Sprite backgroundSp;
    backgroundSp.setTexture(MenuActivity::background);
    window->draw(backgroundSp);

    window->draw(this->button.buttonSP);

    if (button.clicked(gameState)) {
        std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>();
        gameState.setCurrentActivity(std::move(fight));
    }
}