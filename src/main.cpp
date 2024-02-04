
#include <SFML/Graphics.hpp>
#include "draw/draw.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        sf::Texture texture = draw();
        sf::Sprite sprite;
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
    }
    return 0;
}