
#include "GameState.hpp"
#include "SFML/Graphics.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Texture background;
    if (!background.loadFromFile("../../src/ressources/start_background.png")) {
        std::cout << "load image" << std::endl;
    }
    sf::Texture gear;
    if (!gear.loadFromFile("../../src/ressources/gear.png")) {
        std::cout << "load image" << std::endl;
    }

    GameState gameState;
    FightActivity fightActivity;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        fightActivity.displayActivity(window, background, gear);
        window.display();
    }
    return 0;
}