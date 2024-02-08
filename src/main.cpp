
#include "GameState.hpp"
#include "SFML/Graphics.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PnC ");

    GameState gameState = GameState(window);
    FightActivity fightActivity;
    Activity activity;
    activity = fightActivity;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        gameState.startActivity(*(gameState.gameWindow), gameState.textures.background, gameState.textures.gear);
        window.display();
    }
    return 0;
}