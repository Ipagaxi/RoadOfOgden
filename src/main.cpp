
#include <SFML/Graphics.hpp>
#include "draw.hpp"
#include "FightActivity.hpp"
#include <iostream>

using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Texture background;
    if (!background.loadFromFile("../../src/ressources/start_background.png")) {
        cout << "load image" << endl;
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        FightActivity activity;
        activity.displayActivity(window, background);
        window.display();
    }
    return 0;
}