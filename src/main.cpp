
#include <SFML/Graphics.hpp>
#include "draw.hpp"
#include "FightActivity.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        FightActivity activity;
        activity.displayActivity(window);
        window.display();
    }
    return 0;
}